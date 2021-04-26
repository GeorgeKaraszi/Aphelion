#ifndef APINCLUDE_PCH_HPP
#define APINCLUDE_PCH_HPP

#include "macros.h"

#ifndef NOMINMAX
    #define NOMINMAX
#endif

#ifndef DIRECTINPUT_VERSION
  #define DIRECTINPUT_VERSION 0x0800
#endif

#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <dxgi.h>
#include <dxgi1_2.h>
#include <dinput.h>
#include <cassert>
#include <Resources/resource.h>

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dwmapi.lib")

#endif // APINCLUDE_PCH_HPP