#ifndef TLOC_TYPES_INL
#define TLOC_TYPES_INL

#ifndef TLOC_TYPES_H
#error "Must include header before including the inline file"
#endif

namespace tloc
{
#define COND_TYPE_TEMP_FALSE ConditionalType<T, T_DeclareValue>

  template <typename T, bool T_DeclareValue>
  TL_FI COND_TYPE_TEMP_FALSE::ConditionalType() {}

  template <typename T, bool T_DeclareValue>
  TL_FI COND_TYPE_TEMP_FALSE::ConditionalType(const T& aValue)
  {
    TLOC_UNUSED(aValue);
  }

  template <typename T, bool T_DeclareValue>
  TL_FI COND_TYPE_TEMP_FALSE&
    COND_TYPE_TEMP_FALSE::operator= (const COND_TYPE_TEMP_FALSE& aOther)
  {
    TLOC_UNUSED(aOther);
    return *this;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI COND_TYPE_TEMP_FALSE&
    COND_TYPE_TEMP_FALSE::operator= (const T& aOther)
  {
    TLOC_UNUSED(aOther);
    return *this;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI T
    COND_TYPE_TEMP_FALSE::operator+ (const COND_TYPE_TEMP_FALSE& aOther) const
  {
    TLOC_UNUSED(aOther);
    return g_conditional_type_invalid_value;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI T
    COND_TYPE_TEMP_FALSE::operator+ (const T& aOther) const
  {
    TLOC_UNUSED(aOther);
    return g_conditional_type_invalid_value;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI T
    COND_TYPE_TEMP_FALSE::operator- (const COND_TYPE_TEMP_FALSE& aOther) const
  {
    TLOC_UNUSED(aOther);
    return g_conditional_type_invalid_value;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI T
    COND_TYPE_TEMP_FALSE::operator- (const T& aOther) const
  {
    TLOC_UNUSED(aOther);
    return g_conditional_type_invalid_value;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI T
    COND_TYPE_TEMP_FALSE::operator* (const COND_TYPE_TEMP_FALSE& aOther) const
  {
    TLOC_UNUSED(aOther);
    return g_conditional_type_invalid_value;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI T
    COND_TYPE_TEMP_FALSE::operator* (const T& aOther) const
  {
    TLOC_UNUSED(aOther);
    return g_conditional_type_invalid_value;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI T
    COND_TYPE_TEMP_FALSE::operator/ (const COND_TYPE_TEMP_FALSE& aOther) const
  {
    TLOC_UNUSED(aOther);
    return g_conditional_type_invalid_value;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI T
    COND_TYPE_TEMP_FALSE::operator/ (const T& aOther) const
  {
    TLOC_UNUSED(aOther);
    return g_conditional_type_invalid_value;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI COND_TYPE_TEMP_FALSE&
    COND_TYPE_TEMP_FALSE::operator+= (const COND_TYPE_TEMP_FALSE& aOther)
  {
    TLOC_UNUSED(aOther);
    return *this;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI COND_TYPE_TEMP_FALSE&
    COND_TYPE_TEMP_FALSE::operator+= (const T& aOther)
  {
    TLOC_UNUSED(aOther);
    return *this;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI COND_TYPE_TEMP_FALSE&
    COND_TYPE_TEMP_FALSE::operator-= (const COND_TYPE_TEMP_FALSE& aOther)
  {
    TLOC_UNUSED(aOther);
    return *this;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI COND_TYPE_TEMP_FALSE&
    COND_TYPE_TEMP_FALSE::operator-= (const T& aOther)
  {
    TLOC_UNUSED(aOther);
    return *this;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI COND_TYPE_TEMP_FALSE&
    COND_TYPE_TEMP_FALSE::operator*= (const COND_TYPE_TEMP_FALSE& aOther)
  {
    TLOC_UNUSED(aOther);
    return *this;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI COND_TYPE_TEMP_FALSE&
    COND_TYPE_TEMP_FALSE::operator*= (const T& aOther)
  {
    TLOC_UNUSED(aOther);
    return *this;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI COND_TYPE_TEMP_FALSE&
    COND_TYPE_TEMP_FALSE::operator/= (const COND_TYPE_TEMP_FALSE& aOther)
  {
    TLOC_UNUSED(aOther);
    return *this;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI COND_TYPE_TEMP_FALSE&
    COND_TYPE_TEMP_FALSE::operator/= (const T& aOther)
  {
    TLOC_UNUSED(aOther);
    return *this;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI COND_TYPE_TEMP_FALSE&
    COND_TYPE_TEMP_FALSE::operator++()
  {
    return *this;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI COND_TYPE_TEMP_FALSE
    COND_TYPE_TEMP_FALSE::operator++(int)
  {
    return *this;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI COND_TYPE_TEMP_FALSE&
    COND_TYPE_TEMP_FALSE::operator--()
  {
    return *this;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI COND_TYPE_TEMP_FALSE
    COND_TYPE_TEMP_FALSE::operator--(int)
  {
    return *this;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI bool
    COND_TYPE_TEMP_FALSE::operator==(const this_type& aOther) const
  {
    TLOC_UNUSED(aOther);
    return false;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI bool
    COND_TYPE_TEMP_FALSE::operator==(const T& aOther) const
  {
    TLOC_UNUSED(aOther);
    return false;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI bool
    COND_TYPE_TEMP_FALSE::operator!=(const this_type& aOther) const
  {
    TLOC_UNUSED(aOther);
    return false;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI bool
    COND_TYPE_TEMP_FALSE::operator!=(const T& aOther) const
  {
    TLOC_UNUSED(aOther);
    return false;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI bool
    COND_TYPE_TEMP_FALSE::operator< (const this_type& aOther) const
  {
    TLOC_UNUSED(aOther);
    return false;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI bool
    COND_TYPE_TEMP_FALSE::operator< (const T& aOther) const
  {
    TLOC_UNUSED(aOther);
    return false;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI bool
    COND_TYPE_TEMP_FALSE::operator<=(const this_type& aOther) const
  {
    TLOC_UNUSED(aOther);
    return false;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI bool
    COND_TYPE_TEMP_FALSE::operator<=(const T& aOther) const
  {
    TLOC_UNUSED(aOther);
    return false;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI bool
    COND_TYPE_TEMP_FALSE::operator>=(const this_type& aOther) const
  {
    TLOC_UNUSED(aOther);
    return false;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI bool
    COND_TYPE_TEMP_FALSE::operator>=(const T& aOther) const
  {
    TLOC_UNUSED(aOther);
    return false;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI bool
    COND_TYPE_TEMP_FALSE::operator> (const this_type& aOther) const
  {
    TLOC_UNUSED(aOther);
    return false;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI bool
    COND_TYPE_TEMP_FALSE::operator> (const T& aOther) const
  {
    TLOC_UNUSED(aOther);
    return false;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI const T&
    COND_TYPE_TEMP_FALSE::get() const
  {
    return g_conditional_type_invalid_value;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI T
    COND_TYPE_TEMP_FALSE::value() const
  {
    return g_conditional_type_invalid_value;
  }

#define COND_TYPE_TEMP_TRUE ConditionalType<T, true>

  template <typename T>
  TL_FI COND_TYPE_TEMP_TRUE::ConditionalType() {}

  template <typename T>
  TL_FI COND_TYPE_TEMP_TRUE::ConditionalType(const T& aValue)
    : m_value(aValue) {}

  template <typename T>
  TL_FI COND_TYPE_TEMP_TRUE&
    COND_TYPE_TEMP_TRUE::operator= (const COND_TYPE_TEMP_TRUE& aOther)
  {
    m_value = aOther.value();
    return *this;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP_TRUE&
    COND_TYPE_TEMP_TRUE::operator= (const T& aOther)
  {
    m_value = aOther;
    return *this;
  }

  template <typename T>
  TL_FI T
    COND_TYPE_TEMP_TRUE::operator+ (const COND_TYPE_TEMP_TRUE& aOther) const
  {
    return value() + aOther.value();
  }

  template <typename T>
  TL_FI T
    COND_TYPE_TEMP_TRUE::operator+ (const T& aOther) const
  {
    return value() + aOther;
  }

  template <typename T>
  TL_FI T
    COND_TYPE_TEMP_TRUE::operator- (const COND_TYPE_TEMP_TRUE& aOther) const
  {
    return value() - aOther.value();
  }

  template <typename T>
  TL_FI T
    COND_TYPE_TEMP_TRUE::operator- (const T& aOther) const
  {
    return value() - aOther;
  }

  template <typename T>
  TL_FI T
    COND_TYPE_TEMP_TRUE::operator* (const COND_TYPE_TEMP_TRUE& aOther) const
  {
    return value() * aOther.value();
  }

  template <typename T>
  TL_FI T
    COND_TYPE_TEMP_TRUE::operator* (const T& aOther) const
  {
    return value() * aOther;
  }

  template <typename T>
  TL_FI T
    COND_TYPE_TEMP_TRUE::operator/ (const COND_TYPE_TEMP_TRUE& aOther) const
  {
    return value() / aOther.value();
  }

  template <typename T>
  TL_FI T
    COND_TYPE_TEMP_TRUE::operator/ (const T& aOther) const
  {
    return value() / aOther;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP_TRUE&
    COND_TYPE_TEMP_TRUE::operator+= (const COND_TYPE_TEMP_TRUE& aOther)
  {
    m_value += aOther.m_value;
    return *this;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP_TRUE&
    COND_TYPE_TEMP_TRUE::operator+= (const T& aOther)
  {
    m_value += aOther;
    return *this;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP_TRUE&
    COND_TYPE_TEMP_TRUE::operator-= (const COND_TYPE_TEMP_TRUE& aOther)
  {
    m_value -= aOther.m_value;
    return *this;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP_TRUE&
    COND_TYPE_TEMP_TRUE::operator-= (const T& aOther)
  {
    m_value -= aOther;
    return *this;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP_TRUE&
    COND_TYPE_TEMP_TRUE::operator*= (const COND_TYPE_TEMP_TRUE& aOther)
  {
    m_value *= aOther.m_value;
    return *this;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP_TRUE&
    COND_TYPE_TEMP_TRUE::operator*= (const T& aOther)
  {
    m_value *= aOther;
    return *this;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP_TRUE&
    COND_TYPE_TEMP_TRUE::operator/= (const COND_TYPE_TEMP_TRUE& aOther)
  {
    m_value /= aOther.m_value;
    return *this;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP_TRUE&
    COND_TYPE_TEMP_TRUE::operator/= (const T& aOther)
  {
    m_value /= aOther;
    return *this;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP_TRUE&
    COND_TYPE_TEMP_TRUE::operator++()
  {
    ++m_value;
    return *this;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP_TRUE
    COND_TYPE_TEMP_TRUE::operator++(int)
  {
    COND_TYPE_TEMP_TRUE temp(m_value);
    ++m_value;
    return temp;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP_TRUE&
    COND_TYPE_TEMP_TRUE::operator--()
  {
    --m_value;
    return *this;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP_TRUE
    COND_TYPE_TEMP_TRUE::operator--(int)
  {
    COND_TYPE_TEMP_TRUE temp(m_value);
    --m_value;
    return temp;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP_TRUE::operator==(const this_type& aOther) const
  {
    return m_value == aOther.m_value;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP_TRUE::operator==(const T& aOther) const
  {
    return m_value == aOther;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP_TRUE::operator!=(const this_type& aOther) const
  {
    return m_value != aOther.m_value;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP_TRUE::operator!=(const T& aOther) const
  {
    return m_value != aOther;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP_TRUE::operator< (const this_type& aOther) const
  {
    return m_value < aOther.m_value;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP_TRUE::operator< (const T& aOther) const
  {
    return m_value < aOther;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP_TRUE::operator<=(const this_type& aOther) const
  {
    return m_value <= aOther.m_value;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP_TRUE::operator<=(const T& aOther) const
  {
    return m_value <= aOther;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP_TRUE::operator>=(const this_type& aOther) const
  {
    return m_value >= aOther.m_value;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP_TRUE::operator>=(const T& aOther) const
  {
    return m_value >= aOther;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP_TRUE::operator> (const this_type& aOther) const
  {
    return m_value > aOther.m_value;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP_TRUE::operator> (const T& aOther) const
  {
    return m_value > aOther;
  }

  template <typename T>
  TL_FI const T&
    COND_TYPE_TEMP_TRUE::get() const
  {
    return m_value;
  }

  template <typename T>
  TL_FI T
    COND_TYPE_TEMP_TRUE::value() const
  {
    return m_value;
  }

};

#endif