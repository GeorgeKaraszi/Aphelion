#include "Network.hpp"

static ApCore::Core::Network* g_network = nullptr;

namespace ApCore::Core
{
  Network *Network::GetNetwork()
  {
    return g_network;
  }

  Network::Network(const char* api_key) : m_api_key(api_key)
  {
    assert(BLANK_PTR(g_network) && "There exists an Instance of ApCore::Core::Network already!");
    m_websocket = std::make_shared<Nets::WebSocket>(this);
    m_census    = std::make_shared<Nets::CensusAPI>(this);
    g_network   = this;
  }

  Network::~Network()
  {
    m_ioc.stop();
    m_websocket.reset();
    m_census.reset();
    g_network = nullptr;
  }

  void Network::AsyncRun()
  {
    if(!m_runnable)
      return;

    if(m_ioc.stopped())
      m_ioc.restart();

    m_census->PollQueue();
    m_ioc.poll_one();
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