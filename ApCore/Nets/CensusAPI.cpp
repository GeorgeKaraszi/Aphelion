#include "CensusAPI.hpp"
#include <ApCore/Core/Network.hpp>
#include <utility>
#include <iostream>

namespace ApCore::Nets
{
  CensusAPI::CensusAPI(ApCore::Core::Network *network) : m_network(network)
  {
    std::string outfit_lookup_schema = R"(
      ?alias_lower=%s
      &c:join=character
        ^on:leader_character_id
        ^to:character_id
        ^inject_at:outfits_faction
        ^show:faction_id
      &c:join=outfit_member
      ^inject_at:members
      ^list:1
      (
          character
          ^inject_at:character
          ^show:character_id'name.first'faction_id'profile_id
          (
              profile
                ^on:profile_id
                ^inject_at:profile
                ^show:profile_type_description'image_path,
              characters_online_status
                ^inject_at:status
                ^hide:character_id
          )
      )
    )";

    // Strip out all the nice looking whitespace and new lines displayed in the string literal.
    boost::remove_erase_if(outfit_lookup_schema, boost::is_any_of(" \n"));
    m_outfit_lookup_schema = std::move(outfit_lookup_schema);
  }

  JSON CensusAPI::GetOutfitRoster(const std::string& outfit_tag)
  {
    char request[512];
    auto lc_tag = boost::to_lower_copy(outfit_tag);
    sprintf_s(request, 512, m_outfit_lookup_schema.c_str(), lc_tag.c_str());

    auto uri = ApCore::Modules::Uri::CensusUri(m_network->m_api_key, "/get/ps2/outfit", request);
    return FetchHttpData(uri);
  }

  JSON CensusAPI::GetImageData(const std::string_view &image_path)
  {
    auto uri = ApCore::Modules::Uri::CensusUri(m_network->m_api_key, image_path.data());
    return FetchHttpData(uri);
  }

  JSON CensusAPI::FetchHttpData(const ApCore::Modules::Uri &uri)
  {
    auto stream   = beast::tcp_stream(net::make_strand(m_ioc));
    http::request<http::string_body> req = { http::verb::get, uri.Request, 11 };
    http::response<http::string_body> res;
    beast::flat_buffer buffer;
    beast::error_code ec;
    auto error_handle = [&](const char* what) {
      if(!ec)
      {
        return false;
      }

      // TODO: LOG and deal with errors from HTTP stream
      stream.socket().shutdown(tcp::socket::shutdown_both, ec);
      return true;
    };

    req.set(http::field::host, uri.Host);
    req.set(http::field::user_agent, PIL_USER_AGENT);

    stream.connect(m_network->Resolve(uri));

    http::write(stream, req, ec);

    if(error_handle("PollQueue::http::write")) return JSON();

    http::read(stream, buffer, res, ec);

    if(error_handle("PollQueue::http::read")) return JSON();

    stream.socket().shutdown(tcp::socket::shutdown_both, ec);
    auto parsed_body = JSON::parse(res.body());

    return JSON::parse(res.body());
  }

}