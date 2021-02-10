#include "Network.hpp"
#include <stdexcept>
#include <utility>

static ApCore::Core::Network* g_network = nullptr;

namespace ApCore::Core
{
  Network *Network::GetNetwork()
  {
    AP_ASSERT(PRESENT_PTR(g_network), "Network has not been initialized")
    return g_network;
  }

  Network::Network(std::string api_key) : m_api_key(std::move(api_key))
  {
    assert(BLANK_PTR(g_network) && "There exists an Instance of ApCore::Core::Network already!");
    m_websocket = std::make_shared<Nets::WebSocket>(this);
    m_census    = std::make_shared<Nets::CensusAPI>(this);
    g_network   = this;
  }

  Network::~Network()
  {
    Shutdown();
    m_websocket.reset();
    m_census.reset();
    g_network = nullptr;
  }

  void Network::AsyncRun()
  {
    try
    {
      if (!m_runnable)
        return;

      m_websocket->DoRead();
    }
    catch(...)
    {
      std::cout << "Exception in Network Thread!: " << boost::current_exception_diagnostic_information() << std::endl;
    }
  }

  void Network::Shutdown()
  {
    m_runnable = false;

    if(!m_ioc.stopped())
    {
      m_ioc.stop();
    }
  }

  std::shared_ptr<Nets::WebSocket> Network::GetWebSocket()
  {
    return m_websocket;
  }

  std::shared_ptr<Nets::CensusAPI> Network::GetCensusAPI()
  {
    return m_census;
  }
}