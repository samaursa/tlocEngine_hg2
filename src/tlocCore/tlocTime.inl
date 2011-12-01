#include "tlocTypes.inl"
#include "tlocPlatform.h"

#ifndef TLOC_TIME_H
#error "Must include header before including the inline file"
#endif
#include "tlocTime.h"

#if defined(TLOC_WIN32) || defined(TLOC_WIN64)
#include <Windows.h>
#endif

namespace tloc { namespace core {

  //////////////////////////////////////////////////////////////////////////
  // Macros

#define TIMER_TYPES typename T_Real, typename T_UInt, bool T_Adjust
#define TIMER_PARAMS T_Real, T_UInt, T_Adjust

  //////////////////////////////////////////////////////////////////////////
  // Timer

  //------------------------------------------------------------------------
  // Main Functions

  template <TIMER_TYPES>
  Timer<TIMER_PARAMS>::Timer()
  {
    Calibrate();
  }

  template <TIMER_TYPES>
  Timer<TIMER_PARAMS>::~Timer()
  {
  }

  template <TIMER_TYPES>
  TL_I void Timer<TIMER_PARAMS>::Calibrate(bool aCalibrate)
  {
    if (aCalibrate)
    {
      m_adjustInSeconds = 0;
      Reset();
      m_adjustInSeconds = ElapsedSeconds();
    }

    Reset();
  }

  template <TIMER_TYPES>
  TL_I void Timer<TIMER_PARAMS>::Reset()
  {
    DoReset(PlatformInfo<>::GetPlatformType());
  }

  template <TIMER_TYPES>
  TL_I T_Real Timer<TIMER_PARAMS>::ElapsedSeconds()
  {
    return DoGetElapsedSeconds(PlatformInfo<>::GetPlatformType());
  }

  template <TIMER_TYPES>
  TL_I T_UInt Timer<TIMER_PARAMS>::ElapsedMilliSeconds()
  {
    return DoGetElapsedMilliSeconds(PlatformInfo<>::GetPlatformType());
  }

  template <TIMER_TYPES>
  TL_I T_UInt Timer<TIMER_PARAMS>::ElapsedMicroSeconds()
  {
    return DoGetElapsedMicroSeconds(PlatformInfo<>::GetPlatformType());
  }

  //------------------------------------------------------------------------
  // Helper functions

  //````````````````````````````````````````````````````````````````````````
  // DoReset()

  template <TIMER_TYPES>
  TL_I void Timer<TIMER_PARAMS>::DoReset(Platform_win32)
  {
    QueryPerformanceCounter( (LARGE_INTEGER*) &m_start);
  }

  template <TIMER_TYPES>
  TL_I void Timer<TIMER_PARAMS>::DoReset(Platform_osx)
  {
    TLOC_ASSERT_WIP();
  }

  template <TIMER_TYPES>
  TL_I void Timer<TIMER_PARAMS>::DoReset(Platform_osx_iphone)
  {
    TLOC_ASSERT_WIP();
  }

  template <TIMER_TYPES>
  TL_I void Timer<TIMER_PARAMS>::DoReset(Platform_ps3)
  {
    TLOC_ASSERT_WIP();
  }

  template <TIMER_TYPES>
  TL_I void Timer<TIMER_PARAMS>::DoReset(Platform_linux)
  {
    TLOC_ASSERT_WIP();
  }

  //````````````````````````````````````````````````````````````````````````
  // DoGetElapsedSeconds()

  template <TIMER_TYPES>
  TL_I T_Real Timer<TIMER_PARAMS>::DoGetElapsedSeconds(Platform_win32)
  {
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);

    LARGE_INTEGER end;
    QueryPerformanceCounter( &end);

    T_UInt delta = end.QuadPart - m_start;

    return (delta / (T_Real)freq.QuadPart) + m_adjustInSeconds;
  }

  template <TIMER_TYPES>
  TL_I T_Real Timer<TIMER_PARAMS>::DoGetElapsedSeconds(Platform_osx)
  {
    TLOC_ASSERT_WIP();
    return 0;
  }

  template <TIMER_TYPES>
  TL_I T_Real Timer<TIMER_PARAMS>::DoGetElapsedSeconds(Platform_osx_iphone)
  {
    TLOC_ASSERT_WIP();
    return 0;
  }

  template <TIMER_TYPES>
  TL_I T_Real Timer<TIMER_PARAMS>::DoGetElapsedSeconds(Platform_ps3)
  {
    TLOC_ASSERT_WIP();
    return 0;
  }

  template <TIMER_TYPES>
  TL_I T_Real Timer<TIMER_PARAMS>::DoGetElapsedSeconds(Platform_linux)
  {
    TLOC_ASSERT_WIP();
    return 0;
  }

  //````````````````````````````````````````````````````````````````````````
  // DoGetElapsedMilliSeconds()

  template <TIMER_TYPES>
  TL_I T_UInt Timer<TIMER_PARAMS>::DoGetElapsedMilliSeconds(Platform_win32)
  {
    return (T_UInt)(ElapsedSeconds() * (T_Real)1000.0);
  }

  template <TIMER_TYPES>
  TL_I T_UInt Timer<TIMER_PARAMS>::DoGetElapsedMilliSeconds(Platform_osx)
  {
    TLOC_ASSERT_WIP();
    return 0;
  }

  template <TIMER_TYPES>
  TL_I T_UInt Timer<TIMER_PARAMS>::DoGetElapsedMilliSeconds(Platform_osx_iphone)
  {
    TLOC_ASSERT_WIP();
    return 0;
  }

  template <TIMER_TYPES>
  TL_I T_UInt Timer<TIMER_PARAMS>::DoGetElapsedMilliSeconds(Platform_ps3)
  {
    TLOC_ASSERT_WIP();
    return 0;
  }

  template <TIMER_TYPES>
  TL_I T_UInt Timer<TIMER_PARAMS>::DoGetElapsedMilliSeconds(Platform_linux)
  {
    TLOC_ASSERT_WIP();
    return 0;
  }

  //````````````````````````````````````````````````````````````````````````
  // DoGetElapsedMicroSeconds()

  template <TIMER_TYPES>
  TL_I T_UInt Timer<TIMER_PARAMS>::DoGetElapsedMicroSeconds(Platform_win32)
  {
    return (T_UInt)(ElapsedSeconds() * (T_Real)1000000.0);
  }

  template <TIMER_TYPES>
  TL_I T_UInt Timer<TIMER_PARAMS>::DoGetElapsedMicroSeconds(Platform_osx)
  {
    TLOC_ASSERT_WIP();
    return 0;
  }

  template <TIMER_TYPES>
  TL_I T_UInt Timer<TIMER_PARAMS>::DoGetElapsedMicroSeconds(Platform_osx_iphone)
  {
    TLOC_ASSERT_WIP();
    return 0;
  }

  template <TIMER_TYPES>
  TL_I T_UInt Timer<TIMER_PARAMS>::DoGetElapsedMicroSeconds(Platform_ps3)
  {
    TLOC_ASSERT_WIP();
    return 0;
  }

  template <TIMER_TYPES>
  TL_I T_UInt Timer<TIMER_PARAMS>::DoGetElapsedMicroSeconds(Platform_linux)
  {
    TLOC_ASSERT_WIP();
    return 0;
  }

};};
