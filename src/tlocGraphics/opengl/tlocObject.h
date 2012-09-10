#ifndef TLOC_GL_OBJECT_H
#define TLOC_GL_OBJECT_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/utilities/tlocUtils.h>

#include <tlocCore/base_classes/tlocNonCopyable.h>

namespace tloc { namespace graphics { namespace gl {

  class Object : public core::NonCopyable
  {
  public:
    typedef u32 object_handle;

    Object() {}

    TLOC_DECL_AND_DEF_GETTERS_DIRECT(object_handle, GetHandle, m_handle);

  private:

    object_handle m_handle;
  };

};};};

#endif