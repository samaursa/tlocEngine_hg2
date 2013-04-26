#ifndef _TLOC_MATH_ANGLE_H_
#define _TLOC_MATH_ANGLE_H_

#include <tlocMath/tlocMathBase.h>

#include <tlocCore/utilities/tlocUtils.h>

namespace tloc { namespace math { namespace types {

  template <typename T, class T_Derived>
  class Angle_T
  {
  public:
    TLOC_STATIC_ASSERT_IS_ARITH(T);

  public:
    typedef T                                     value_type;
    typedef T_Derived                             derived_type;
    typedef Angle_T<value_type, derived_type>     this_type;

  public:
    Angle_T(value_type a_angle = 0);

    template <typename T_AngleType>
    Angle_T(T_AngleType a_angle);

    this_type&    operator=(value_type a_angle);
    this_type&    operator=(const this_type& a_other);

    template <typename T_AngleType>
    this_type&    operator=(const T_AngleType& a_angle);

    template <typename T_AngleType>
    value_type    GetAs() const;
    TLOC_DECL_AND_DEF_GETTER(value_type, Get, m_angle);

    this_type   operator+  (this_type a_other) const;
    this_type&  operator+= (this_type a_other) ;

    this_type   operator-  (this_type a_other) const;
    this_type&  operator-= (this_type a_other) ;

    this_type   operator*  (this_type a_other) const;
    this_type&  operator*= (this_type a_other) ;

    this_type   operator/  (this_type a_other) const;
    this_type&  operator/= (this_type a_other) ;

    bool operator <  (this_type a_other) const;
    bool operator == (this_type a_other) const;
    TLOC_DECLARE_OPERATORS(this_type);

  protected:
    typedef type_true     fundamental_type;
    typedef type_false    angle_type;

    void DoSetAngleCtor(value_type, fundamental_type);
    template <typename T_AngleType>
    void DoSetAngleCtor(T_AngleType, angle_type);

    value_type    m_angle;
  };

  //////////////////////////////////////////////////////////////////////////
  // Radian

  template <typename T>
  class Radian_T : protected Angle_T<T, Radian_T<T> >
  {
  public:
    template <typename U, class V> friend class Angle_T;

    typedef Radian_T<T>              this_type;
    typedef Angle_T<T, this_type>    base_type;

    typedef typename base_type::value_type  value_type;

    using base_type::operator+;
    using base_type::operator+=;
    using base_type::operator-;
    using base_type::operator-=;
    using base_type::operator*;
    using base_type::operator*=;
    using base_type::operator/;
    using base_type::operator/=;

    using base_type::operator<;
    using base_type::operator==;
    using base_type::operator!=;
    using base_type::operator>;
    using base_type::operator<=;
    using base_type::operator>=;

    using base_type::GetAs;
    using base_type::Get;
    using base_type::m_angle;

  public:
    Radian_T(value_type a_angle = 0);

    template <typename T_AngleType>
    Radian_T(T_AngleType a_angle);

    template <typename T_AngleType>
    this_type&    operator=(const T_AngleType& a_angle);

    value_type GetAsDegree() const;

  private:
    template <typename T_AngleType>
    void DoSetAngle(T_AngleType a_angle);
    void DoSetAngle(this_type a_angle);

    template <typename T_AngleType>
    value_type DoGetAs(T_AngleType) const;
    value_type DoGetAs(this_type) const;
  };

  //////////////////////////////////////////////////////////////////////////
  // Degree

  template <typename T>
  class Degree_T : protected Angle_T<T, Degree_T<T> >
  {
  public:
    template <typename U, class V> friend class Angle_T;

    typedef Degree_T<T>              this_type;
    typedef Angle_T<T, this_type>    base_type;

    typedef typename base_type::value_type  value_type;

    using base_type::operator+;
    using base_type::operator+=;
    using base_type::operator-;
    using base_type::operator-=;
    using base_type::operator*;
    using base_type::operator*=;
    using base_type::operator/;
    using base_type::operator/=;

    using base_type::operator<;
    using base_type::operator==;
    using base_type::operator!=;
    using base_type::operator>;
    using base_type::operator<=;
    using base_type::operator>=;

    using base_type::GetAs;
    using base_type::Get;
    using base_type::m_angle;

  public:
    Degree_T(value_type a_angle = 0);

    template <typename T_AngleType>
    Degree_T(T_AngleType a_angle);

    template <typename T_AngleType>
    this_type&    operator=(const T_AngleType& a_angle);

    value_type GetAsRadian() const;

  private:
    template <typename T_AngleType>
    void DoSetAngle(T_AngleType a_angle);
    void DoSetAngle(this_type a_angle);

    template <typename T_AngleType>
    value_type DoGetAs(T_AngleType) const;
    value_type DoGetAs(this_type) const;
  };

  //////////////////////////////////////////////////////////////////////////
  // Template definitions

  template <typename T, class T_Derived>
  template <typename T_AngleType>
  Angle_T<T, T_Derived>::
    Angle_T(T_AngleType a_angle)
  {
    typedef Loki::TypeTraits<T_AngleType>                 unknown_type;
    typedef Loki::Int2Type<unknown_type::isFundamental>   resolved_angle_type;

    TLOC_STATIC_ASSERT(
      ( Loki::Conversion<T_AngleType, this_type>::exists2Way ||
        Loki::TypeTraits<T_AngleType>::isFloat),
        T_AngleType_must_be_derived_from_Angle_T_or_must_be_value_type);

    // Select the type to cast to, this is necessary for f32 and f64 (does
    // nothing for Radian or Degree) to allow casting from f32 to f64. An
    // unfortunate side-effect is that f64 to f32 casts will be implicit but
    // hopefully no angle will be big enough
    typedef Loki::Select<Loki::TypeTraits<T_AngleType>::isFloat,
      value_type, T_AngleType>::Result  cast_to;

    DoSetAngleCtor(static_cast<cast_to>(a_angle), resolved_angle_type() );
  }

  template <typename T, class T_Derived>
  template <typename T_AngleType>
  void Angle_T<T, T_Derived>::
    DoSetAngleCtor(T_AngleType a_angle, angle_type)
  {
    TLOC_STATIC_ASSERT(
      (Loki::IsSameType<value_type, T_AngleType::value_type>::value),
      value_types_are_not_the_same);

    static_cast<derived_type*>(this)->DoSetAngle(a_angle);
  }

  //------------------------------------------------------------------------
  // Radian

  template <typename T>
  template <typename T_AngleType>
  Radian_T<T>::
    Radian_T(T_AngleType a_angle)
    : base_type(a_angle)
  {
    TLOC_STATIC_ASSERT(
      ( Loki::Conversion<T_AngleType, base_type>::exists2Way ||
        Loki::TypeTraits<T_AngleType>::isFloat),
        T_AngleType_must_be_derived_from_Angle_T);
  }

  //------------------------------------------------------------------------
  // Degree

  template <typename T>
  template <typename T_AngleType>
  Degree_T<T>::
    Degree_T(T_AngleType a_angle)
    : base_type(a_angle)
  {
    TLOC_STATIC_ASSERT(
      ( Loki::Conversion<T_AngleType, base_type>::exists2Way ||
        Loki::TypeTraits<T_AngleType>::isFloat),
        T_AngleType_must_be_derived_from_Angle_T);
  }

  //////////////////////////////////////////////////////////////////////////
  // Typedefs

  typedef Radian_T<tl_float>      Radian;
  typedef Radian_T<f32>           radian_f32;
  typedef Radian_T<f64>           radian_f64;

  typedef Degree_T<tl_float>      Degree;
  typedef Degree_T<f32>           degree_f32;
  typedef Degree_T<f64>           degree_f64;

};};};

#endif