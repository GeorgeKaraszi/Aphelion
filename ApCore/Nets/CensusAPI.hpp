#ifndef APCORE_NETS_CENSUSAPI_HPP
#define APCORE_NETS_CENSUSAPI_HPP

#include <queue>
#include <set>
#include <string>
#include <ApInclude/boost.hpp>
#include <ApCore/Modules/Uri.hpp>
#include <ApTools/Eventing/Event.hpp>

namespace ApCore::Core { class Network; }

namespace ApCore::Nets
{
  class CensusAPI
  {
    using CALLBACK_EVENT = ApTools::Eventing::Event<const JSON&>;
  public:
    explicit CensusAPI(ApCore::Core::Network *network);
    void PollQueue();
    void QueueOutfitRoster(const std::string& outfit_tag);
    void QueueImageData(const std::string_view &image_path);

  private:
    void AddToQueue(ApCore::Modules::Uri &uri, CALLBACK_EVENT *callback);

  public:
    CALLBACK_EVENT OutfitRosterEvent;
    CALLBACK_EVENT ImageDataEvent;

  private:
    ApCore::Core::Network *m_network;
    std::string m_outfit_lookup_schema;
    std::queue<std::pair<ApCore::Modules::Uri, CALLBACK_EVENT*>> m_queue;
  };
}

#endif //APCORE_NETS_CENSUSAPI_HPP
