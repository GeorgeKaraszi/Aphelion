#ifndef APWINDOW_CMONITOR_INFO_EX_HPP
#define APWINDOW_CMONITOR_INFO_EX_HPP

#include <vector>
#include <dwmapi.h>

class CMonitorInfoEx : public MONITORINFOEX
{
public:
  CMonitorInfoEx();

  [[nodiscard]] LPCRECT GetRect()     const { return &rcMonitor; }
  [[nodiscard]] LPCRECT GetWorkRect() const { return &rcWork; }
  [[nodiscard]] LPCTSTR DeviceName()  const { return szDevice; }

  [[nodiscard]]  bool IsPrimary()     const { return dwFlags & MONITORINFOF_PRIMARY; }
  [[nodiscard]]  bool IsSecondary()   const { return !IsPrimary(); }

  [[nodiscard]]  int Width()          const { return rcMonitor.right - rcMonitor.left; }
  [[nodiscard]]  int Height()         const { return rcMonitor.bottom - rcMonitor.top; }
  [[nodiscard]]  int WorkWidth()      const { return rcWork.right - rcWork.left; }
  [[nodiscard]]  int WorkHeight()     const { return rcWork.bottom - rcWork.top; }
};


class CSysDisplays
{
public:
  CSysDisplays();

  void Update();

  [[nodiscard]]  int Count() const;
  [[nodiscard]]  const CMonitorInfoEx& Get( int i ) const;
  [[nodiscard]]  const CMonitorInfoEx& GetPrimary() const;
  [[nodiscard]]  const CMonitorInfoEx& GetSecondary() const;

private:
  std::vector<CMonitorInfoEx> mInfo;
};

#endif //APWINDOW_CMONITOR_INFO_EX_HPP
