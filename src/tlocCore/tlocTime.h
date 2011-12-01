#ifndef TLOC_TIME_H
#define TLOC_TIME_H

#include "tlocBase.h"
#include "tlocTypes.h"
#include "tlocPlatform.h"

namespace tloc { namespace core {

  template <typename T_Real = f64, typename T_UInt = u64, bool T_Adjust = true>
  class Timer
  {
  public:
    Timer();
    ~Timer();

    //////////////////////////////////////////////////////////////////////////////
    /// <summary>Calibrates the timer if T_Adjust = true.</summary>
    ///
    /// <remarks> Use this function to re-calibrate a timer. This function is
    ///           automatically called when the timer is first created.</remarks>
    ///
    /// <param name="aCalibrate">(optional) default is true.</param>
    TL_I void       Calibrate(bool aCalibrate = T_Adjust);
    TL_I void       Reset();
    TL_I T_Real     ElapsedSeconds();
    TL_I T_UInt     ElapsedMilliSeconds();
    TL_I T_UInt     ElapsedMicroSeconds();

  private:

    TL_I void       DoReset(Platform_win32);
    TL_I void       DoReset(Platform_osx);
    TL_I void       DoReset(Platform_osx_iphone);
    TL_I void       DoReset(Platform_ps3);
    TL_I void       DoReset(Platform_linux);

    TL_I T_Real     DoGetElapsedSeconds(Platform_win32);
    TL_I T_Real     DoGetElapsedSeconds(Platform_osx);
    TL_I T_Real     DoGetElapsedSeconds(Platform_osx_iphone);
    TL_I T_Real     DoGetElapsedSeconds(Platform_ps3);
    TL_I T_Real     DoGetElapsedSeconds(Platform_linux);

    TL_I T_UInt     DoGetElapsedMilliSeconds(Platform_win32);
    TL_I T_UInt     DoGetElapsedMilliSeconds(Platform_osx);
    TL_I T_UInt     DoGetElapsedMilliSeconds(Platform_osx_iphone);
    TL_I T_UInt     DoGetElapsedMilliSeconds(Platform_ps3);
    TL_I T_UInt     DoGetElapsedMilliSeconds(Platform_linux);

    TL_I T_UInt     DoGetElapsedMicroSeconds(Platform_win32);
    TL_I T_UInt     DoGetElapsedMicroSeconds(Platform_osx);
    TL_I T_UInt     DoGetElapsedMicroSeconds(Platform_osx_iphone);
    TL_I T_UInt     DoGetElapsedMicroSeconds(Platform_ps3);
    TL_I T_UInt     DoGetElapsedMicroSeconds(Platform_linux);

    T_UInt                              m_start;
    ConditionalType<T_Real, T_Adjust>   m_adjustInSeconds;

  };

};};

#endif