#ifndef _TLOC_CORE_INCLUDE_ALL_SMART_PTR_H_
#define _TLOC_CORE_INCLUDE_ALL_SMART_PTR_H_

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/smart_ptr/tlocSmartPtr.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/smart_ptr/tlocUniquePtr.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.h>
#include <tlocCore/smart_ptr/tlocVirtualStackObject.h>

#define TLOC_TYPEDEF_ALL_SMART_PTRS(_type_, _typedef_)\
  TLOC_TYPEDEF_UNIQUE_PTR(_type_, _typedef_);\
  TLOC_TYPEDEF_VIRTUAL_PTR(_type_, _typedef_);\
  TLOC_TYPEDEF_SHARED_PTR(_type_, _typedef_)

#define TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(_type_)\
  TLOC_EXTERN_TEMPLATE_UNIQUE_PTR(_type_);\
  TLOC_EXTERN_TEMPLATE_VIRTUAL_PTR(_type_);\
  TLOC_EXTERN_TEMPLATE_SHARED_PTR(_type_)

namespace tloc
{
  TLOC_TYPEDEF_ALL_SMART_PTRS(char8, char8);
  TLOC_TYPEDEF_ALL_SMART_PTRS(uchar8, uchar8);
  TLOC_TYPEDEF_ALL_SMART_PTRS(char32, char32);
  TLOC_TYPEDEF_ALL_SMART_PTRS(ushort, ushort);
  TLOC_TYPEDEF_ALL_SMART_PTRS(s8, s8);
  TLOC_TYPEDEF_ALL_SMART_PTRS(s16, s16);
  TLOC_TYPEDEF_ALL_SMART_PTRS(s32, s32);
  TLOC_TYPEDEF_ALL_SMART_PTRS(s64, s64);
  TLOC_TYPEDEF_ALL_SMART_PTRS(f32, f32);
  TLOC_TYPEDEF_ALL_SMART_PTRS(f64, f64);

  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(char8, char8);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(uchar8, uchar8);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(char32, char32);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(ushort, ushort);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(s8, s8);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(s16, s16);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(s32, s32);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(s64, s64);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(f32, f32);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(f64, f64);
}

#endif