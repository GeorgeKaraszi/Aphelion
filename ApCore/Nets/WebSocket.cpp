#include "WebSocket.hpp"
#include <ApCore/Core/Network.hpp>
#include <ApCore/Modules/RootCertificate.hpp>

namespace ApCore::Nets
{
  WebSocket::WebSocket(ApCore::Core::Network *network) : m_network(network)
  {
    ApCore::Modules::load_root_certificates(m_ctx);
    m_uri = ApCore::Modules::Uri::WebsocketUri(m_network->m_api_key);
    m_ws  = new ssl_ws { m_ioc, m_ctx };
    DataEvent += [] (const JSON& data) { std::cout << data.dump() << std::endl; };
    Connect();
  }

  WebSocket::~WebSocket()
  {
    Disconnect();
    m_ioc.stop();
    delete m_ws;
    m_ws = nullptr;
  }

  void WebSocket::Connect()
  {
    beast::error_code ec;
    auto const results = m_network->Resolve(m_uri);
    net::connect(get_lowest_layer(*m_ws), results, ec);

    if(BoostError(ec))
      return;

    if(!SSL_set_tlsext_host_name(m_ws->next_layer().native_handle(), m_uri.Host.c_str()))
    {
      throw beast::system_error(
          beast::error_code(static_cast<int>(::ERR_get_error()), net::error::get_ssl_category()),
          "Failed to set SNI Hostname"
       );
    }

    m_ws->next_layer().handshake(ssl::stream_base::client);
    m_ws->set_option(websocket::stream_base::timeout::suggested(beast::role_type::client));
    m_ws->set_option(websocket::stream_base::decorator([](websocket::request_type &req) {
       req.set(http::field::user_agent, PIL_USER_AGENT);
     }
    ));

    m_ws->handshake(m_uri.Host, m_uri.Request, ec);

    BoostError(ec);
  }

  void WebSocket::Disconnect()
  {
    if(IsConnected())
    {
      m_ws->close(websocket::close_code::normal);
    }
  }

  bool WebSocket::IsConnected()
  {
    return PRESENT_PTR(m_ws) && m_ws->is_open();
  }

  bool WebSocket::DoRead()
  {
    beast::error_code ec;
    beast::flat_buffer buffer;

    if (m_ioc.stopped())
      m_ioc.restart();

    m_ws->read(buffer, ec);

    if(BoostError(ec))
      return false;

    std::string_view buffer_view = { (char *) buffer.data().data(), buffer.size() };

    if (!buffer_view.empty() && !IsDuplicate(buffer_view))
    {
//        JSON json_buffer = JSON::parse(buffer_view, nullptr, false, true);
      JSON json_buffer = JSON::parse(buffer_view);
      DataEvent.Invoke(json_buffer);
    }

    return true;
  }

  bool WebSocket::DoWrite(const std::string_view &buffer)
  {
    beast::error_code ec;
    auto message_buffer = net::buffer(buffer);

    if (m_ioc.stopped())
      m_ioc.restart();

    m_ws->write(message_buffer, ec);
    DataEvent.Invoke(JSON::parse(buffer));

    return !BoostError(ec);
  }

  bool WebSocket::IsDuplicate(const std::string_view &buffer)
  {
    size_t msg_hash          = m_hash_fn(buffer);
    size_t array_idx         = msg_hash % m_message_log.max_size();
    bool duplicate_found     = m_message_log[array_idx] == msg_hash;
    m_message_log[array_idx] = msg_hash;

    return duplicate_found;
  }

  bool WebSocket::BoostError(beast::error_code ec)
  {
    if(ec)
    {
      std::cerr << __FUNCTION__ << " Error: " << ec.message() << std::endl;
      return true;
    }

    return false;
  }

}