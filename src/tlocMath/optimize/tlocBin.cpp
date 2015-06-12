#include "tlocBin.h"

namespace tloc { namespace math { namespace optimize {

  // ///////////////////////////////////////////////////////////////////////
  // Case

  auto
    Case::
    GetX() const -> value_type
  { return m_rectangle.GetPosition()[0]; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Case::
    GetY() const -> value_type
  { return m_rectangle.GetPosition()[1]; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Case::
    SetX(value_type a_x) -> this_type& 
  { 
    m_rectangle.SetPosition(core_ds::MakeTuple(a_x, GetY())); 
    return *this; 
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Case::
    SetY(value_type a_y) -> this_type& 
  { 
    m_rectangle.SetPosition(core_ds::MakeTuple(GetX(), a_y)); 
    return *this; 
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Case::
    GetWidth() const -> value_type
  { return m_rectangle.GetWidth(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Case::
    GetHeight() const -> value_type
  { return m_rectangle.GetHeight(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Case::
    SetWidth(value_type a_x) -> this_type&
  { m_rectangle.SetWidth(a_x); return *this; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Case::
    SetHeight(value_type a_y) -> this_type&
  { m_rectangle.SetHeight(a_y); return *this; }

  // ///////////////////////////////////////////////////////////////////////
  // Bin

  Bin::
    Bin()
    : m_bimDimensions(core_ds::MakeTuple(32, 32))
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Bin::
    Bin(dim_type a_startingDimension)
    : m_bimDimensions(a_startingDimension)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    Bin::
    push_back(const case_type& a_case)
  {
    m_cases.push_back(a_case);
  }

};};};