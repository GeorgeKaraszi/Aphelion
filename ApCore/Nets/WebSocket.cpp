#include "WebSocket.hpp"
#include <ApCore/Core/Network.hpp>
#include <ApCore/Modules/RootCertificate.hpp>

namespace ApCore::Nets
{
  WebSocket::WebSocket(ApCore::Core::Network *network) : m_network(network)
  {
    ApCore::Modules::load_root_certificates(m_ctx);
    m_uri = ApCore::Modules::Uri::WebsocketUri(m_network->m_api_key);
    m_ws  = new ssl_stream_ws { m_network->GenerateIOC(), m_ctx };
  }

  WebSocket::~WebSocket()
  {
    Disconnect();
    delete m_ws;
  }

  void WebSocket::Connect()
  {
    beast::error_code ec;
    auto const results = m_network->Resolve(m_uri);

    beast::get_lowest_layer(*m_ws).expires_after(std::chrono::seconds(15));
    beast::get_lowest_layer(*m_ws).connect(results, ec);

    if (ec)
    {
      // TODO: Deal with fail here.
      return;
    }

    beast::get_lowest_layer(*m_ws).expires_never();
    m_ws->next_layer().handshake(ssl::stream_base::client);
    m_ws->set_option(websocket::stream_base::timeout::suggested(beast::role_type::client));
    m_ws->set_option(websocket::stream_base::decorator([](websocket::request_type &req) {
     req.set(http::field::user_agent, PIL_USER_AGENT);
    }
    ));

    m_ws->handshake(m_uri.Host, m_uri.Request, ec);

    if (ec)
    {
      // TODO: Deal with handshake failure here
    }
  }

  void WebSocket::Disconnect()
  {
    if(!IsConnected())
    {
      return;
    }

    m_ws->close(websocket::close_code::normal);
  }

  bool WebSocket::IsConnected()
  {
    return m_ws->is_open();
  }

  void WebSocket::SubmitMessage(const std::string_view &msg)
  {
    auto buffer = net::buffer(msg);
    m_ws->async_write(
        buffer,
        beast::bind_front_handler(&WebSocket::OnWrite, shared_from_this())
   );
  }

  void WebSocket::OnWrite(beast::error_code ec, std::size_t bytes_transferred)
  {
    boost::ignore_unused(bytes_transferred);

    if (ec)
    {
      // TODO: Deal with chained OnWrite Error call here
      return;
    }

    // Read a message into our buffer
    m_ws->async_read(
        m_buffer,
        beast::bind_front_handler(&WebSocket::OnRead, shared_from_this())
    );
  }

  void WebSocket::OnRead(beast::error_code ec, std::size_t bytes_transferred)
  {
    boost::ignore_unused(bytes_transferred);
    if (ec)
    {
      m_ws->async_read(
          m_buffer,
          beast::bind_front_handler(&WebSocket::OnRead, shared_from_this())
      );

      // TODO: Log read failure. Note: this could just be an incomplete message or we disconnected.
      return;
    }

    std::string_view buffer_view = { (char *) m_buffer.data().data(), m_buffer.size() };

    if(!IsDuplicate(buffer_view))
    {
      JSON json_buffer = JSON::parse(buffer_view);
      DataEvent.Invoke(json_buffer);
    }

    m_buffer.clear();

    // Continue to add jobs to read messages
    m_ws->async_read(
        m_buffer,
        beast::bind_front_handler(&WebSocket::OnRead, shared_from_this())
    );
  }

  bool WebSocket::IsDuplicate(const std::string_view &buffer)
  {
    size_t msg_hash      = m_hash_fn(buffer);
    size_t array_idx     = msg_hash % m_message_log.max_size();
    bool duplicate_found = m_message_log[array_idx] == msg_hash;

    m_message_log[array_idx] = msg_hash;

    return duplicate_found;
  }

}