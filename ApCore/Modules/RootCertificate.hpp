#ifndef APCORE_MODULES_ROOTCERTIFICATE_HPP
#define APCORE_MODULES_ROOTCERTIFICATE_HPP

#include <ApInclude/boost.hpp>

namespace ApCore::Modules
{
  void load_root_certificates(ssl::context& ctx, boost::system::error_code& ec);
  void load_root_certificates(ssl::context& ctx);
}

#endif //APCORE_MODULES_ROOTCERTIFICATE_HPP
