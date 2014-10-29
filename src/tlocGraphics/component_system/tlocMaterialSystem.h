#pragma once
#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_MATERIAL_SYSTEM_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_MATERIAL_SYSTEM_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/component_system/tlocEntityProcessingSystem.h>
#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocEntity.h>

#include <tlocGraphics/opengl/tlocShaderProgram.h>

namespace tloc { namespace graphics { namespace component_system {

  class MaterialSystem : public core::component_system::EntityProcessingSystem
  {
  public:
    typedef core::component_system::EntityProcessingSystem  base_type;

  public:
    MaterialSystem(event_manager_ptr a_eventMgr,
                   entity_manager_ptr a_entityMgr);

    virtual error_type InitializeEntity(entity_ptr a_ent);
    virtual error_type ShutdownEntity(entity_ptr a_ent);

    virtual void ProcessEntity(entity_ptr a_ent, f64 a_deltaT);

    virtual void OnComponentDisable(const core_cs::EntityComponentEvent&) {}
    virtual void OnComponentEnable(const core_cs::EntityComponentEvent&) {}
  };

  //------------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(MaterialSystem, material_system);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_NO_DEF_CTOR(MaterialSystem, material_system);

  // -----------------------------------------------------------------------
  // extern template

  TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(MaterialSystem);
  TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(MaterialSystem);

};};};

#endif