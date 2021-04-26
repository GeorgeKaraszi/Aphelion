#ifndef APINCLUDE_FAST_ATIO_HPP
#define APINCLUDE_FAST_ATIO_HPP

inline int fast_atoi(const char *str)
{
  int val = 0;
  while(*str) { val = val * 10 + (*str++ - '0'); }
  return val;
}

inline int fast_atoi(const std::string &str)
{
  return str.empty() ? 0 : fast_atoi(str.c_str());
}
#endif //APINCLUDE_FAST_ATIO_HPP
