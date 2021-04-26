#ifndef APCORE_CORE_NETWORK_HPP
#define APCORE_CORE_NETWORK_HPP

#ifndef PIL_USER_AGENT
    #define PIL_USER_AGENT "PIL-OVERLAY-v1.0"
#endif

#include <string>
#include <ApInclude/macros.h>
#include <ApCore/Nets/CensusAPI.hpp>
#include <ApCore/Nets/WebSocket.hpp>

#pragma comment (lib, "crypt32.lib")

namespace ApCore::Core
{
  class Network
  {
  public:
    static Network *GetNetwork();

  public:
    Network()               = delete;
    Network(const Network&) = delete;
    explicit Network(std::string api_key);
    ~Network();

    void AsyncRun();
    void Shutdown();
    [[nodiscard]]
    bool IsRunning() const { return m_runnable; }
    bool HasAPIKey() const { return !m_api_key.empty(); }
    std::shared_ptr<Nets::WebSocket> GetWebSocket();
    std::shared_ptr<Nets::CensusAPI> GetCensusAPI();

  protected:
    inline auto GenerateIOC()                    { return net::make_strand(m_ioc); }
    inline auto Resolve(const Modules::Uri& uri) { return m_resolver.resolve(uri.Host, uri.Port); }

  protected:
    bool m_runnable = true;
    net::io_context m_ioc;

  private:
    std::string     m_api_key;
    tcp::resolver   m_resolver { net::make_strand(m_ioc) };

  private:
    std::shared_ptr<Nets::WebSocket> m_websocket;
    std::shared_ptr<Nets::CensusAPI> m_census;

    friend class ApCore::Nets::WebSocket;
    friend class ApCore::Nets::CensusAPI;
  };
}

#endif //APCORE_CORE_NETWORK_HPP
