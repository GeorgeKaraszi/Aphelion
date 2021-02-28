#ifndef APINCLUDE_STRING_HELPER_HPP
#define APINCLUDE_STRING_HELPER_HPP

#include <string>
#include <memory>
#include <stdexcept>

inline std::string to_string(double val, const char *precision)
{
  const auto _Len = static_cast<size_t>(_scprintf(precision, val));
  std::string _Str(_Len, '\0');
  sprintf_s(&_Str[0], _Len + 1, precision, val);
  return _Str;
}

inline std::string to_string(float val, const char *precision)
{
  return to_string(static_cast<double>(val), precision);
}

template<typename ... Args>
inline std::string format_string(const std::string &format, Args ... args)
{
  int size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
  if( size <= 0 )
  {
    throw std::runtime_error("Error during formatting.");
  }

  std::unique_ptr<char[]> buf(new char[ size ]);

  snprintf(buf.get(), size, format.c_str(), args...);
  return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

#endif //APINCLUDE_STRING_HELPER_HPP
