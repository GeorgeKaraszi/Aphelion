#ifndef APINCLUDES__MACROS_H
#define APINCLUDES__MACROS_H

#define BLANK_PTR(x) (x == nullptr)
#define PRESENT_PTR(x) (x != nullptr)
#define ReleaseCOM(x) { if(x){ x->Release(); x = nullptr; } }
#define HR(x) (x)


#endif // APINCLUDES__MACROS_H
