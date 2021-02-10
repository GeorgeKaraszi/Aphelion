#ifndef APINCLUDE_STRING_HELPER_HPP
#define APINCLUDE_STRING_HELPER_HPP

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

#endif //APINCLUDE_STRING_HELPER_HPP
