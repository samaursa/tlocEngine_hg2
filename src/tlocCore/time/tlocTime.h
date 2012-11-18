#ifndef TLOC_TIME_H
#define TLOC_TIME_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/platform/tlocPlatform.h>

namespace tloc { namespace core {

  template <typename T_Real = f64, typename T_UInt = u64, bool T_Adjust = true>
  class Timer_T
  {
  public:
    typedef T_Real    sec_type;
    typedef T_UInt    value_type;

    Timer_T();
    ~Timer_T();

    ///-------------------------------------------------------------------------
    /// Calibrates the timer if T_Adjust = true.
    ///
    /// @param  aCalibrate (optional) default is true.
    ///
    /// ### remarks
    /// Use this function to re-calibrate a timer. This function is
    /// automatically called when the timer is first created.
    ///-------------------------------------------------------------------------
    TL_I void       Calibrate(bool aCalibrate = T_Adjust);
    TL_I void       Reset();
    TL_I sec_type   ElapsedSeconds();
    TL_I value_type ElapsedMilliSeconds();
    TL_I value_type ElapsedMicroSeconds();

  private:

#ifdef TLOC_OS_IPHONE
    TL_I static sec_type   DoGetTicksToSeconds();
#endif

    TL_I void       DoInit();
    TL_I void       DoReset();
    TL_I sec_type   DoGetElapsedSeconds();
    TL_I value_type DoGetElapsedMilliSeconds();
    TL_I value_type DoGetElapsedMicroSeconds();

    value_type                              m_start;
    ConditionalType<sec_type, T_Adjust>     m_adjustInSeconds;

#ifdef TLOC_OS_IPHONE
    static const sec_type                         sm_ticksToSeconds;
#endif

  };

  //------------------------------------------------------------------------
  // Typedefs

  typedef Timer_T<>             Timer;
  typedef Timer_T<f32, u32>     Timer32;
  typedef Timer_T<f64, u64>     Timer64;

};};

#endif