#ifndef _TLOC_GRAPHICS_GL_TEXTURE_OBJECT_H_
#define _TLOC_GRAPHICS_GL_TEXTURE_OBJECT_H_

#include <tlocCore/tloc_core.h>
#include <tlocGraphics/opengl/tlocObject.h>
#include <tlocGraphics/media/tlocImage.h>

namespace tloc { namespace graphics { namespace gl {

  namespace p_texture_object {
    namespace target
    {
      typedef s32 enum_type; // s32 because GLint is s32

      struct Tex1D                 { static const enum_type s_glParamName; };
      struct Tex2D                 { static const enum_type s_glParamName; };
      struct Tex3D                 { static const enum_type s_glParamName; };

      struct TexRectangle          { static const enum_type s_glParamName; };
      struct TexCubeMap            { static const enum_type s_glParamName; };
      struct TexBuffer             { static const enum_type s_glParamName; };
      struct Tex2DMultiSample      { static const enum_type s_glParamName; };

      struct Tex1DArray            { static const enum_type s_glParamName; };
      struct Tex2DArray            { static const enum_type s_glParamName; };
      struct TexCubeMapArray       { static const enum_type s_glParamName; };
      struct Tex2DMultiSampleArray { static const enum_type s_glParamName; };
    };
  };

  class TextureObject
    : public Object_T<TextureObject, p_object::WithError>
  {
  public:
    template <typename T> friend class ObjectRefCounted;

  public:
    typedef Object_T<TextureObject, p_object::WithError>  base_type;
    typedef base_type::object_handle                      object_handle;
    typedef base_type::error_type                         error_type;
    typedef p_texture_object::target::enum_type           texture_type;
    typedef media::Image                                  image_type;

  public:
    TextureObject();
    ~TextureObject();

    template <typename T_Target>
    error_type  Bind();
    error_type  Load(const image_type& a_image);

    error_type  Activate(s32 a_texUnit);

  private:
    error_type  DoBind(texture_type a_texType);

  private:
    texture_type m_texType;

  };

  //------------------------------------------------------------------------
  // Template method definitions

  template <typename T_Target>
  TextureObject::error_type TextureObject::
    Bind()
  {
    using namespace p_texture_object::target;

    // TODO: Support the rest of the image formats
    //type_traits::AssertTypeIsSupported
    //  <T_Target,
    //   Tex1D, Tex2D, Tex3D,
    //   TexRectangle, TexCubeMap, TexBuffer, Tex2DMultiSample,
    //   Tex1DArray, Tex2DArray, TexCubeMapArray, Tex2DMultiSampleArray>();

    type_traits::AssertTypeIsSupported
      <T_Target,
      Tex2D, TexCubeMap>();
    return DoBind(T_Target::s_glParamName);
  }

};};};

#endif