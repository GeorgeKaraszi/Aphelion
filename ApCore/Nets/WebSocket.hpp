#ifndef APCORE_NETS_WEBSOCKET_HPP
#define APCORE_NETS_WEBSOCKET_HPP

#include <string>
#include <queue>
#include <ApInclude/boost.hpp>
#include <ApCore/Modules/Uri.hpp>
#include <ApTools/Eventing/Event.hpp>

namespace ApCore::Core { class Network; }

namespace ApCore::Nets
{
  class WebSocket
  {
  public:
    WebSocket()                 = delete;
    WebSocket(const WebSocket&) = delete;
    explicit WebSocket(ApCore::Core::Network *network);
    ~WebSocket();

    void Connect();
    void Disconnect();
    bool IsConnected();

    bool DoRead();
    bool DoWrite(const std::string_view &buffer);

  private:
    bool IsDuplicate(const std::string_view &buffer);
    static inline bool BoostError(beast::error_code ec);

  public:
    ApTools::Eventing::Event<const JSON&> DataEvent;

  private:
    ssl_ws*                     m_ws       { nullptr };
    ssl::context                m_ctx      { ssl::context::tlsv12_client };
    net::io_context             m_ioc;
    Modules::Uri                m_uri;

  private:
    ApCore::Core::Network      *m_network;
    beast::flat_buffer          m_buffer;
    std::hash<std::string_view> m_hash_fn;
    std::array<size_t, 10>      m_message_log {};
  };
}

#endif //APCORE_NETS_WEBSOCKET_HPP
