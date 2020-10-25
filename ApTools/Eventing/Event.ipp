#include "Event.hpp"

template<class... ArgTypes>
ApTools::Eventing::ListenerID ApTools::Eventing::Event<ArgTypes...>::AddListener(Callback callback)
{
  ListenerID current_id = m_next_listener_id++;
  m_callbacks.emplace(current_id, callback);
  return current_id;
}

template<class... ArgTypes>
ApTools::Eventing::ListenerID ApTools::Eventing::Event<ArgTypes...>::operator+=(Callback callback)
{
  return AddListener(callback);
}

template<class... ArgTypes>
bool ApTools::Eventing::Event<ArgTypes...>::RemoveListener(ListenerID listener_id)
{
  return m_callbacks.erase(listener_id) != 0;
}

template<class... ArgTypes>
bool ApTools::Eventing::Event<ArgTypes...>::operator-=(ListenerID listener_id)
{
  return RemoveListener(listener_id);
}

template<class... ArgTypes>
void ApTools::Eventing::Event<ArgTypes...>::RemoveAllListeners()
{
  m_callbacks.clear();
}

template<class... ArgTypes>
size_t ApTools::Eventing::Event<ArgTypes...>::GetListenerCount()
{
  return m_callbacks.size();
}

template<class... ArgTypes>
void ApTools::Eventing::Event<ArgTypes...>::Invoke(ArgTypes... args)
{
  for(auto const&[key, value] : m_callbacks)
  {
    value(args...);
  }
}