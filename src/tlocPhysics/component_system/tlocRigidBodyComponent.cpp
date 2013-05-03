#include "tlocRigidBodyComponent.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl>
#include <tlocCore/component_system/tlocComponentPoolManager.inl>

namespace tloc { namespace physics { namespace component_system{

  RigidBody::
    RigidBody(rigid_body_def_sptr a_rigidBodyDef)
    : base_type(k_component_type)
    , m_rigidBodyDef(a_rigidBodyDef)
  {
  }

  //////////////////////////////////////////////////////////////////////////
  // Explicit instantiations

  template class core::smart_ptr::SharedPtr<RigidBody>;
  template class core::component_system::ComponentPool_TI<RigidBodyPtr>;

};};};
