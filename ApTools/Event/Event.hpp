#ifndef APTOOLS_EVENT_EVENT_HPP
#define APTOOLS_EVENT_EVENT_HPP

#include <functional>

namespace ApTools::Event
{
  using ListenerID = uint64_t;

  template<class... ArgTypes>
  class Event
  {
  public:
    using Callback = std::function<void(ArgTypes...)>;

    ListenerID AddListener(Callback callback);
    ListenerID operator+=(Callback callback);

    bool RemoveListener(ListenerID listener_id);
    bool operator-=(ListenerID listener_id);

    void RemoveAllListeners();
    size_t GetListenerCount();

    void Invoke(ArgTypes... args);
  private:
    std::unordered_map<ListenerID, Callback> m_callbacks;
    ListenerID                               m_next_listener_id;
  };
}

#include <ApTools/Event/Event.ipp>

#endif // APTOOLS_EVENT_EVENT_HPP
