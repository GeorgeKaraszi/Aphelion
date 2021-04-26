#include "cmonitorinfo_ex.hpp"

BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
  std::vector<CMonitorInfoEx>& infoArray = *reinterpret_cast< std::vector<CMonitorInfoEx>* >(dwData);
  CMonitorInfoEx info;
  GetMonitorInfo(hMonitor, &info);
  infoArray.push_back(info);
  return TRUE;
}

CMonitorInfoEx::CMonitorInfoEx() : tagMONITORINFOEXW()
{
  cbSize = sizeof(MONITORINFOEX);
}


CSysDisplays::CSysDisplays()
{
  Update();
}

void CSysDisplays::Update()
{
  mInfo.clear();
  mInfo.reserve(::GetSystemMetrics(SM_CMONITORS));
  EnumDisplayMonitors(nullptr, nullptr, MonitorEnumProc, reinterpret_cast<LPARAM>(&mInfo));
}

int CSysDisplays::Count() const
{
  return (int)mInfo.size();
}


const CMonitorInfoEx& CSysDisplays::Get( int i ) const
{
  return mInfo[i];
}

const CMonitorInfoEx& CSysDisplays::GetPrimary() const
{

  for(auto &info : mInfo)
  {
    if(info.IsPrimary())
    {
      return info;
    }
  }

  return Get(0);
}

const CMonitorInfoEx& CSysDisplays::GetSecondary() const
{

  for(auto &info : mInfo)
  {
    if(info.IsSecondary())
    {
      return info;
    }
  }

  return Get(0);
}