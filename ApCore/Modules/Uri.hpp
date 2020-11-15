#ifndef APCORE_MODULES_URI_HPP
#define APCORE_MODULES_URI_HPP

#include <string>

namespace ApCore::Modules
{
  struct Uri
  {
    typedef typename std::string_view basic_string;
  public:
    std::string ApiKey, Protocol, Host, Port, Request;

    static Uri WebsocketUri(const basic_string &api_key)
    {
      Uri results  = {
          .ApiKey        = api_key.data(),
          .Protocol      = "wss",
          .Host          = "push.planetside2.com",
          .Port          = "443",
          .Request       = std::string("/streaming?environment=ps2&service-id=s:").append(api_key)
      };

      return results;
    }

    static Uri CensusUri(const basic_string &api_key, const basic_string &path, const basic_string &request = {})
    {
      std::string fmt_request;
      fmt_request.reserve(api_key.size() + path.size() + request.size() + 3);
      fmt_request.append("/s:").append(api_key).append(path).append(request);

      Uri results  = {
          .ApiKey        = api_key.data(),
          .Protocol      = "http",
          .Host          = "census.daybreakgames.com",
          .Port          = "80",
          .Request       = fmt_request
      };

      return results;
    }
  };  // uri
}

#endif //APCORE_MODULES_URI_HPP
