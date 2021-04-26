#ifndef APCORE_NETS_CENSUSAPI_HPP
#define APCORE_NETS_CENSUSAPI_HPP

#include <queue>
#include <set>
#include <string>
#include <ApInclude/boost.hpp>
#include <ApCore/Modules/Uri.hpp>
#include <ApTools/Eventing/Event.hpp>
#include <ApInclude/macros.h>

namespace ApCore::Core { class Network; }

namespace ApCore::Nets
{
  class CensusAPI
  {
    using CALLBACK_FN = std::function<bool(const JSON&)>;
  public:
    struct alignas(128) RESPONSE
    {
      bool success = true;
      std::string backtrace;
      std::string error;
      JSON data;
    };

  public:
    explicit CensusAPI(ApCore::Core::Network *network);
    RESPONSE GetOutfitRoster(const std::string& outfit_tag);
    RESPONSE GetImageData(const std::string_view &image_path);
    RESPONSE GetCensusQuery(const std::string_view& census_path, const std::string_view& query = "");

  private:
    RESPONSE FetchHttpData(const ApCore::Modules::Uri &uri);

  private:
    ApCore::Core::Network *m_network;
    net::io_context m_ioc;
    std::string m_outfit_lookup_schema;
  };
}

#endif //APCORE_NETS_CENSUSAPI_HPP
