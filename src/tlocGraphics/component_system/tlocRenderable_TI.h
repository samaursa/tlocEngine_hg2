#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_RENDERABLE_TI_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_RENDERABLE_TI_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocComponent.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/opengl/tlocShaderOperator.h>
#include <tlocGraphics/renderer/tlocDrawCommand.h>

namespace tloc { namespace graphics { namespace component_system {

  template <typename T_Component, tl_int T_ComponentEnumType>
  class Renderable_TI
    : public core_cs::Component_T<T_Component, 
                                  core_cs::component_group::k_graphics, 
                                  T_ComponentEnumType>
  {
  public:
    typedef core_cs::Component_T
      <T_Component,
       core_cs::component_group::k_graphics,
       T_ComponentEnumType>                                 base_type;
    
    typedef Renderable_TI<T_Component,
                          base_type::k_component_type>      this_type;

    typedef typename base_type::component_type              component_type;
    typedef gfx_gl::shader_operator_vso                     so_type;
    typedef gfx_gl::vao_vso                                 vao_vso;
    typedef gfx_gl::vao_vptr                                vao_ptr;
    typedef gfx_rend::mode::value_type                      draw_mode;

  public:
    TLOC_DECL_AND_DEF_GETTER_DIRECT(so_type, GetShaderOperator, m_shaderOp);
    TLOC_DECL_AND_DEF_GETTER_NON_CONST(vao_ptr, GetVAO, m_vao.get());
    TLOC_DECL_AND_DEF_GETTER(draw_mode, GetDrawMode, m_drawMode);

    TLOC_DECL_SETTER_BY_VALUE(draw_mode, SetDrawMode);

  protected:
    Renderable_TI(BufferArg a_debugName);

  private:
    so_type         m_shaderOp;
    vao_vso         m_vao;
    draw_mode       m_drawMode;
  };

  // -----------------------------------------------------------------------
  // template definitions

  template <typename T_Component, tl_int T_ComponentEnumType>
  Renderable_TI<T_Component, T_ComponentEnumType>::
    Renderable_TI(BufferArg a_debugName)
    : base_type(a_debugName)
    , m_drawMode(gfx_rend::mode::k_points)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_Component, tl_int T_ComponentEnumType>
  void
    Renderable_TI<T_Component, T_ComponentEnumType>::
    SetDrawMode(draw_mode a_drawMode)
  { m_drawMode = a_drawMode; }




};};};

#endif