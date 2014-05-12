#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_DEBUG_TRANSFORM_SYSTEM_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_DEBUG_TRANSFORM_SYSTEM_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocEntity.h>

#include <tlocGraphics/component_system/tlocRenderSystem.h>
#include <tlocGraphics/component_system/tlocMaterial.h>
#include <tlocGraphics/component_system/tlocSceneGraphSystem.h>
#include <tlocGraphics/component_system/tlocMaterialSystem.h>
#include <tlocGraphics/component_system/tlocTextureAnimatorSystem.h>

namespace tloc { namespace graphics { namespace component_system {

  class DebugTransformRenderSystem
    : public gfx_cs::RenderSystem_TI<renderer::renderer_sptr>
  {
  public:
    typedef gfx_cs::RenderSystem_TI<renderer::renderer_sptr>      base_type;

  public:
    DebugTransformRenderSystem(event_manager_ptr  a_eventMgr,
                               entity_manager_ptr a_entityMgr);

    ~DebugTransformRenderSystem();

    virtual error_type Pre_Initialize();
    virtual error_type InitializeEntity(entity_ptr a_ent);
    virtual error_type Post_Initialize();

    virtual error_type ShutdownEntity(entity_ptr a_ent);

    virtual void Pre_ProcessActiveEntities(f64 a_deltaT);
    virtual void ProcessEntity(entity_ptr a_ent, f64 a_deltaT);
    virtual void Post_ProcessActiveEntities(f64 a_deltaT);

    virtual void OnComponentInsert(const core_cs::EntityComponentEvent&);
    virtual void OnComponentRemove(const core_cs::EntityComponentEvent&);

    virtual void OnComponentDisable(const core_cs::EntityComponentEvent&);
    virtual void OnComponentEnable(const core_cs::EntityComponentEvent&);

  private:

  };

};};};

#endif