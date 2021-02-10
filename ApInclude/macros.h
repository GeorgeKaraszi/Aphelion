#ifndef APINCLUDES__MACROS_H
#define APINCLUDES__MACROS_H

#include <iostream>

#define BLANK_PTR(x)   ( x == nullptr )
#define PRESENT_PTR(x) ( x != nullptr )
#define ReleaseCOM(x)  { if(x){ (x)->Release(); x = nullptr; } }
#define HR(x) (x)
#define AP_ASSERT(condition, message)\
   (!(condition)) ?\
      (std::cerr << "Assertion failed: (" << #condition << "), "\
      << "function " << __FUNCTION__\
      << ", file " << __FILE__\
      << ", line " << __LINE__ << "."\
      << std::endl << (message) << std::endl, abort(), 0) : 1;


#endif // APINCLUDES__MACROS_H
