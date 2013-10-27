#include "tlocRigidBodyListenerComponent.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

namespace tloc { namespace physics { namespace component_system {

  RigidBodyListener::
    RigidBodyListener(rigid_body_listener_type* a_listener)
    : base_type(k_component_type)
    , m_rigidBodyListener(a_listener)
  {
  }

  //////////////////////////////////////////////////////////////////////////
  // Explicit instantiations

  TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(RigidBodyListener);
  TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(rigid_body_listener_sptr);

};};};