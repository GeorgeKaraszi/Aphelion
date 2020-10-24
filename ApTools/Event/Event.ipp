#include <ApTools/Event/Event.hpp>

#pragma once

namespace ApTools::Event
{
  template<class... ArgTypes>
  ListenerID Event<ArgTypes...>::AddListener(Callback callback)
  {
    ListenerID current_id = m_next_listener_id++;
    m_callbacks.emplace(current_id, callback);
    return current_id;
  }

  template<class... ArgTypes>
  ListenerID Event<ArgTypes...>::operator+=(Callback callback)
  {
    return AddListener(callback);
  }

  template<class... ArgTypes>
  bool Event<ArgTypes...>::RemoveListener(ListenerID listener_id)
  {
    return m_callbacks.erase(listener_id) != 0;
  }

  template<class... ArgTypes>
  bool Event<ArgTypes...>::operator-=(ListenerID listener_id)
  {
    return RemoveListener(listener_id);
  }

  template<class... ArgTypes>
  void Event<ArgTypes...>::RemoveAllListeners()
  {
    m_callbacks.clear();
  }

  template<class... ArgTypes>
  size_t Event<ArgTypes...>::GetListenerCount()
  {
    return m_callbacks.size();
  }

  template<class... ArgTypes>
  void Event<ArgTypes...>::Invoke(ArgTypes... args)
  {
    for(auto const&[key, value] : m_callbacks)
    {
      value(args...);
    }
  }

}