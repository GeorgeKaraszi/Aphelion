#ifndef APCORE_NETS_WEBSOCKET_HPP
#define APCORE_NETS_WEBSOCKET_HPP

#include <string>
#include <ApInclude/boost.hpp>
#include <ApCore/Modules/Uri.hpp>
#include <ApTools/Eventing/Event.hpp>

namespace ApCore::Core { class Network; }

namespace ApCore::Nets
{
  class WebSocket : public std::enable_shared_from_this<WebSocket>
  {
  public:
    WebSocket()                 = delete;
    WebSocket(const WebSocket&) = delete;
    explicit WebSocket(ApCore::Core::Network* network);
    ~WebSocket();

    void Connect();
    void Disconnect();
    bool IsConnected();

    void SubmitMessage(const std::string_view &msg);

  private:
    void OnWrite(beast::error_code ec, std::size_t bytes_transferred);
    void OnRead(beast::error_code ec, std::size_t bytes_transferred);
    bool IsDuplicate(const std::string_view &buffer);

  public:
    ApTools::Eventing::Event<const JSON&> DataEvent;

  private:
    ApCore::Core::Network*      m_network;
    ssl_stream_ws*              m_ws       { nullptr };
    ssl::context                m_ctx      { ssl::context::tlsv12_client };
    Modules::Uri                m_uri;

  private:
    beast::flat_buffer          m_buffer;
    std::hash<std::string_view> m_hash_fn;
    std::array<size_t, 10>      m_message_log {};
  };
}

#endif //APCORE_NETS_WEBSOCKET_HPP
