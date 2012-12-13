#include "tlocShaderOperator.h"

#include <tlocCore/smart_ptr/tlocSmartPtr.inl>
#include <tlocCore/utilities/tlocType.h>
#include <tlocCore/containers/tlocContainers.inl>

#include <tlocMath/vector/tlocVector2.h>
#include <tlocMath/vector/tlocVector3.h>
#include <tlocMath/matrix/tlocMatrix3.h>
#include <tlocMath/matrix/tlocMatrix4.h>

#include <tlocGraphics/opengl/tlocOpenGL.h>
#include <tlocGraphics/opengl/tlocShaderProgram.h>
#include <tlocGraphics/opengl/tlocError.h>
#include <tlocGraphics/opengl/tlocShaderVariableInfo.h>
#include <tlocGraphics/error/tlocErrorTypes.h>

namespace tloc { namespace graphics { namespace gl {

  using namespace tloc::math;

  namespace
  {
    typedef core::tl_array<ShaderVariableInfo>::type   glsl_var_info_cont_type;

    //------------------------------------------------------------------------
    // Cacher

    ///-------------------------------------------------------------------------
    /// @brief Unsafe class, only used internally when variables are cached
    ///-------------------------------------------------------------------------
    struct GLSLCacher_I
    {
      typedef tl_int    data_type;

      GLint   m_location;
      GLint   m_arraySize;
      bool    m_isArray;
      void*   m_data;
    };

    struct GLSLUniformCacher : GLSLCacher_I
    {
      typedef GLSLCacher_I::data_type   data_type;

      enum {data_float, data_float2, data_float3};

      void LoadUniform()
      {
      }

      data_type   m_dataType;
    };

    //------------------------------------------------------------------------
    // Variables

    // u32 because of OpenGL's types
    const u32 g_buffSize = ShaderVariableInfo::g_buffSize;

    //------------------------------------------------------------------------
    // Enums

    enum flags
    {
      k_uniformsCached = 0,
      k_attributesCached,
      k_count
    };

    bool DoCheckIfShaderIsAttached()
    {
      return Get<p_get::CurrentProgram>() != 0;
    }

    //------------------------------------------------------------------------
    // Functions

    void DoSetUniform(const ShaderVariableInfo& a_info, const Uniform& a_uniform)
    {
      using namespace core;

      bool isArray = a_uniform.IsArray();

      switch(a_info.m_type)
      {
      case GL_FLOAT:
        {
          if (isArray == false)
          {
            const f32& f = a_uniform.GetValueAs<f32>();
            glUniform1f(a_info.m_location, f);
          }
          else
          {
            typedef f32               num_type;
            typedef Array<num_type>   array_type;

            array_type const & fa = a_uniform.GetValueAs<array_type>();
            num_type const * faraw = reinterpret_cast<num_type const*>(&(fa[0]));
            GLint arraySize = core::utils::CastTo32<u32>(fa.size() );
            glUniform1fv(a_info.m_location, arraySize, faraw);
          }
          break;
        }
      case GL_FLOAT_VEC2:
        {
          if (isArray == false)
          {
            const Vec2f32& v = a_uniform.GetValueAs<Vec2f32>();
            glUniform2f(a_info.m_location, v[0], v[1]);
          }
          else
          {
            typedef f32               num_type;
            typedef Array<num_type>   array_type;

            array_type const & fa = a_uniform.GetValueAs<array_type>();
            num_type const * faraw = reinterpret_cast<num_type const*>(&(fa[0]));
            GLint arraySize = core::utils::CastTo32<u32>(fa.size() );
            glUniform2fv(a_info.m_location, arraySize, faraw);
          }
        }
      case GL_FLOAT_VEC3:
        {
          if (isArray == false)
          {
            const Vec3f32& v = a_uniform.GetValueAs<Vec3f32>();
            glUniform3f(a_info.m_location, v[0], v[1], v[2]);
          }
          else
          {
            typedef f32               num_type;
            typedef Array<num_type>   array_type;

            array_type const & fa = a_uniform.GetValueAs<array_type>();
            num_type const * faraw = reinterpret_cast<num_type const*>(&(fa[0]));
            GLint arraySize = core::utils::CastTo32<u32>(fa.size() );
            glUniform3fv(a_info.m_location, arraySize, faraw);
          }
          break;
        }
      case GL_FLOAT_VEC4:
        {
          if (isArray == false)
          {
            const Vec4f32& v = a_uniform.GetValueAs<Vec4f32>();
            glUniform4f(a_info.m_location, v[0], v[1], v[2], v[3]);
          }
          else
          {
            typedef f32               num_type;
            typedef Array<num_type>   array_type;

            array_type const & fa = a_uniform.GetValueAs<array_type>();
            num_type const * faraw = reinterpret_cast<num_type const*>(&(fa[0]));
            GLint arraySize = core::utils::CastTo32<u32>(fa.size() );
            glUniform4fv(a_info.m_location, arraySize, faraw);
          }
          break;
        }
      case GL_INT:
        {
          if (isArray == false)
          {
            const s32& i = a_uniform.GetValueAs<s32>();
            glUniform1i(a_info.m_location, i);
            break;
          }
          else
          {
            typedef s32               num_type;
            typedef Array<num_type>   array_type;

            array_type const & fa = a_uniform.GetValueAs<array_type>();
            num_type const * faraw = reinterpret_cast<num_type const*>(&(fa[0]));
            GLint arraySize = core::utils::CastTo32<u32>(fa.size() );
            glUniform1iv(a_info.m_location, arraySize, faraw);
          }
        }
      case GL_INT_VEC2:
        {
          if (isArray == false)
          {
            const Tuple2s32& t = a_uniform.GetValueAs<Tuple2s32>();
            glUniform2i(a_info.m_location, t[0], t[1]);
          }
          else
          {
            typedef s32               num_type;
            typedef Array<num_type>   array_type;

            array_type const & fa = a_uniform.GetValueAs<array_type>();
            num_type const * faraw = reinterpret_cast<num_type const*>(&(fa[0]));
            GLint arraySize = core::utils::CastTo32<u32>(fa.size() );
            glUniform2iv(a_info.m_location, arraySize, faraw);
          }

          break;
        }
      case GL_INT_VEC3:
        {
          if (isArray == false)
          {
            const Tuple3s32& t = a_uniform.GetValueAs<Tuple3s32>();
            glUniform3i(a_info.m_location, t[0], t[1], t[2]);
          }
          else
          {
            typedef s32               num_type;
            typedef Array<num_type>   array_type;

            array_type const & fa = a_uniform.GetValueAs<array_type>();
            num_type const * faraw = reinterpret_cast<num_type const*>(&(fa[0]));
            GLint arraySize = core::utils::CastTo32<u32>(fa.size() );
            glUniform3iv(a_info.m_location, arraySize, faraw);
          }

          break;
        }

      case GL_INT_VEC4:
        {
          if (isArray == false)
          {
            const Tuple4s32& t = a_uniform.GetValueAs<Tuple4s32>();
            glUniform4i(a_info.m_location, t[0], t[1], t[2], t[3]);
          }
          else
          {
            typedef s32               num_type;
            typedef Array<num_type>   array_type;

            array_type const & fa = a_uniform.GetValueAs<array_type>();
            num_type const * faraw = reinterpret_cast<num_type const*>(&(fa[0]));
            GLint arraySize = core::utils::CastTo32<u32>(fa.size() );
            glUniform4iv(a_info.m_location, arraySize, faraw);
          }

          break;
        }
      case GL_FLOAT_MAT2:
        {
          typedef f32                 num_type;

          const Mat2f32& m = a_uniform.GetValueAs<Mat2f32>();
          const GLint matSize = 2 * 2;
          num_type const * faraw = reinterpret_cast<num_type const*>(&(m[0]));
          TLOC_ASSERT(a_info.m_arraySize * matSize == Mat2f32::k_TableSize,
            "Mismatched uniform array size!");
          glUniformMatrix2fv(a_info.m_location, 1, GL_FALSE, faraw);
          break;
        }
      case GL_FLOAT_MAT3:
        {
          typedef f32                 num_type;

          const Mat3f32& m = a_uniform.GetValueAs<Mat3f32>();
          const GLint matSize = 3 * 3;
          num_type const * faraw = reinterpret_cast<num_type const*>(&(m[0]));
          TLOC_ASSERT(a_info.m_arraySize * matSize == Mat3f32::k_TableSize,
            "Mismatched uniform array size!");
          glUniformMatrix3fv(a_info.m_location, 1, GL_FALSE, faraw);
          break;
        }
      case GL_FLOAT_MAT4:
        {
          typedef f32                 num_type;

          const Mat4f32& m = a_uniform.GetValueAs<Mat4f32>();
          const GLint matSize = 4 * 4;
          num_type const * faraw = reinterpret_cast<num_type const*>(&(m[0]));
          TLOC_ASSERT(a_info.m_arraySize * matSize == Mat4f32::k_TableSize,
            "Mismatched uniform array size!");
          glUniformMatrix4fv(a_info.m_location, 1, GL_FALSE, faraw);
          break;
        }
      }
    }

    //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    void DoSetAttribute(const ShaderVariableInfo& a_info,
                        const Attribute& a_attribute)
    {
      using namespace core;

      bool isArray = a_attribute.IsArray();
      bool isVertexArray = a_attribute.IsAttribArray();

      switch(a_info.m_type)
      {
      case GL_FLOAT:
        {
          if (isArray == false)
          {
            const f32& f = a_attribute.GetValueAs<f32>();
            glVertexAttrib1f(a_info.m_location, f);
          }
          else if (isVertexArray)
          {
            typedef f32               num_type;
            typedef Array<num_type>   array_type;

            array_type const & fa = a_attribute.GetValueAs<array_type>();
            num_type const * faraw = reinterpret_cast<num_type const*>(&(fa[0]));
            glVertexAttribPointer
              (a_info.m_location, 1, GL_FLOAT, GL_FALSE, 0, faraw);
            glEnableVertexAttribArray(a_info.m_location);
          }
          else
          {
            typedef f32               num_type;
            typedef Array<num_type>   array_type;

            array_type const & fa = a_attribute.GetValueAs<array_type>();
            num_type const * faraw = reinterpret_cast<num_type const*>(&(fa[0]));
            glVertexAttrib1fv(a_info.m_location, faraw);
          }
          break;
        }
      case GL_FLOAT_VEC2:
        {
          if (isArray == false)
          {
            const Vec2f32& v = a_attribute.GetValueAs<Vec2f32>();
            glVertexAttrib2f(a_info.m_location, v[0], v[1]);
          }
          else if (isVertexArray)
          {
            typedef f32               num_type;
            typedef Array<num_type>   array_type;

            array_type const & fa = a_attribute.GetValueAs<array_type>();
            num_type const * faraw = reinterpret_cast<num_type const*>(&(fa[0]));
            glVertexAttribPointer
              (a_info.m_location, 2, GL_FLOAT, GL_FALSE, 0, faraw);
            glEnableVertexAttribArray(a_info.m_location);
          }
          else
          {
            typedef f32               num_type;
            typedef Array<num_type>   array_type;

            array_type const & fa = a_attribute.GetValueAs<array_type>();
            num_type const * faraw = reinterpret_cast<num_type const*>(&(fa[0]));
            glVertexAttrib2fv(a_info.m_location, faraw);
          }
        }
      case GL_FLOAT_VEC3:
        {
          if (isArray == false)
          {
            const Vec3f32& v = a_attribute.GetValueAs<Vec3f32>();
            glVertexAttrib3f(a_info.m_location, v[0], v[1], v[2]);
          }
          else if (isVertexArray)
          {
            typedef f32               num_type;
            typedef Array<num_type>   array_type;

            array_type const & fa = a_attribute.GetValueAs<array_type>();
            num_type const * faraw = reinterpret_cast<num_type const*>(&(fa[0]));
            glVertexAttribPointer
              (a_info.m_location, 3, GL_FLOAT, GL_FALSE, 0, faraw);
            glEnableVertexAttribArray(a_info.m_location);
          }
          else
          {
            typedef f32               num_type;
            typedef Array<num_type>   array_type;

            array_type const & fa = a_attribute.GetValueAs<array_type>();
            num_type const * faraw = reinterpret_cast<num_type const*>(&(fa[0]));
            glVertexAttrib3fv(a_info.m_location, faraw);
          }
          break;
        }
      case GL_FLOAT_VEC4:
        {
          if (isArray == false)
          {
            const Vec4f32& v = a_attribute.GetValueAs<Vec4f32>();
            glVertexAttrib4f(a_info.m_location, v[0], v[1], v[2], v[3]);
          }
          else if (isVertexArray)
          {
            typedef f32               num_type;
            typedef Array<num_type>   array_type;

            array_type const & fa = a_attribute.GetValueAs<array_type>();
            num_type const * faraw = reinterpret_cast<num_type const*>(&(fa[0]));
            glVertexAttribPointer
              (a_info.m_location, 4, GL_FLOAT, GL_FALSE, 0, faraw);
            glEnableVertexAttribArray(a_info.m_location);
          }
          else
          {
            typedef f32               num_type;
            typedef Array<num_type>   array_type;

            array_type const & fa = a_attribute.GetValueAs<array_type>();
            num_type const * faraw = reinterpret_cast<num_type const*>(&(fa[0]));
            glVertexAttrib4fv(a_info.m_location, faraw);
          }
          break;
        }
      }
    }
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ShaderOperator::
    ShaderOperator() : m_flags(k_count)
  { }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void ShaderOperator::
    AddUniform(const uniform_ptr_type& a_uniform)
  { m_uniforms.push_back(core::MakePair(a_uniform, index_type(-1)) ); }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void ShaderOperator::
    AddAttribute(const attribute_ptr_type& a_attribute)
  { m_attributes.push_back(core::MakePair(a_attribute, index_type(-1)) ); }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void ShaderOperator::
    RemoveUniform(const uniform_ptr_type& a_uniform)
  {
    uniform_iterator itr, itrEnd;
    for(itr = m_uniforms.begin(), itrEnd = m_uniforms.end();
        itr != itrEnd; ++itr)
    {
      if (itr->first.Expose() == a_uniform.Expose())
      { break; }
    }

    if (itr != m_uniforms.end())
    { m_uniforms.erase(itr); }
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void ShaderOperator::
    RemoveAttribute(const attribute_ptr_type& a_attribute)
  {
    attribute_iterator itr, itrEnd;
    for(itr = m_attributes.begin(), itrEnd = m_attributes.end();
        itr != itrEnd; ++itr)
    {
      if (itr->first.Expose() == a_attribute.Expose())
      { break; }
    }

    if (itr != m_attributes.end())
    { m_attributes.erase(itr); }
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void ShaderOperator::
    RemoveAllUniforms()
  {
    m_flags.Unmark(k_uniformsCached);
    m_uniforms.clear();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void ShaderOperator::
    RemoveAllAttributes()
  {
    m_flags.Unmark(k_attributesCached);
    m_attributes.clear();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    void ShaderOperator::
    EnableAllUniforms(const ShaderProgram& a_shaderProgram)
  {
    TLOC_ASSERT(a_shaderProgram.IsLinked(),
                "Shader not linked - did you forget to call Link()?");
    TLOC_ASSERT(m_flags.IsMarked(k_uniformsCached),
      "Uniforms not loaded - did you forget to call PrepareAllUniforms()?");

    const glsl_var_info_cont_type& uniCont = a_shaderProgram.GetUniformInfoRef();

    uniform_cont_type::iterator itr, itrEnd;
    for (itr = m_uniforms.begin(), itrEnd = m_uniforms.end();
         itr != itrEnd; ++itr)
    {
      UniformPtr uniformPtr = itr->first;

      if (itr->second >= 0)
      { DoSetUniform(uniCont[itr->second], *uniformPtr); }
    }
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


  void ShaderOperator::
    EnableAllAttributes(const ShaderProgram& a_shaderProgram)
  {
    TLOC_ASSERT(a_shaderProgram.IsLinked(),
                "Shader not linked - did you forget to call Link()?");
    TLOC_ASSERT(m_flags.IsMarked(k_attributesCached),
      "Attributes not loaded - did you forget to call PrepareAllAttributes()?");

    const glsl_var_info_cont_type&
      attrCont = a_shaderProgram.GetAttributeInfoRef();

    attribute_cont_type::iterator itr, itrEnd;
    for (itr = m_attributes.begin(), itrEnd = m_attributes.end();
         itr != itrEnd; ++itr)
    {
      AttributePtr attribPtr = itr->first;

      // If we already know which info to pick
      if (itr->second >= 0)
      { DoSetAttribute(attrCont[itr->second], *attribPtr); }
    }
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ShaderOperator::error_type
    ShaderOperator::
    PrepareAllUniforms(const ShaderProgram& a_shaderProgram)
  {
    TLOC_ASSERT(a_shaderProgram.IsLinked(),
                "Shader not linked - did you forget to call Link()?");

    const glsl_var_info_cont_type& uniCont = a_shaderProgram.GetUniformInfoRef();

    uniform_cont_type::iterator itr, itrEnd;
    for (itr = m_uniforms.begin(), itrEnd = m_uniforms.end();
         itr != itrEnd; ++itr)
    {
      UniformPtr uniformPtr = itr->first;

      index_type index = 0;
      glsl_var_info_cont_type::const_iterator itrInfo, itrInfoEnd;
      for (itrInfo = uniCont.begin(), itrInfoEnd = uniCont.end();
        itrInfo != itrInfoEnd; ++itrInfo)
      {
        if ( uniformPtr->GetName().compare(itrInfo->m_name.Get()) == 0)
        {
          if ( uniformPtr->GetType() == itrInfo->m_type &&
            itrInfo->m_location != -1)
          {
            itr->second = index;
            DoSetUniform(uniCont[itr->second], *uniformPtr);
          }
          else
          {
            // TODO: Convert this assertion to a log
            TLOC_ASSERT(false, "Mismatched uniform type!");
            return ErrorFailure();
          }
        }
        ++index;
      }
    }

    m_flags.Mark(k_uniformsCached);
    return ErrorSuccess();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ShaderOperator::error_type
    ShaderOperator::
    PrepareAllAttributes(const ShaderProgram& a_shaderProgram)
  {
    TLOC_ASSERT(a_shaderProgram.IsLinked(),
                "Shader not linked - did you forget to call Link()?");

    const glsl_var_info_cont_type&
      attrCont = a_shaderProgram.GetAttributeInfoRef();

    attribute_cont_type::iterator itr, itrEnd;
    for (itr = m_attributes.begin(), itrEnd = m_attributes.end();
         itr != itrEnd; ++itr)
    {
      AttributePtr attribPtr = itr->first;

      index_type index = 0;
      glsl_var_info_cont_type::const_iterator itrInfo, itrInfoEnd;
      for (itrInfo = attrCont.begin(), itrInfoEnd = attrCont.end();
        itrInfo != itrInfoEnd; ++itrInfo)
      {
        if ( attribPtr->GetName().compare(itrInfo->m_name.Get()) == 0)
        {
          if ( attribPtr->GetType() == itrInfo->m_type &&
            itrInfo->m_location  != -1)
          {
            itr->second = index;
            DoSetAttribute(attrCont[itr->second], *attribPtr);
          }
          else
          {
            // TODO: Convert this assertion to a log
            TLOC_ASSERT(false, "Mismatched attribute type!");
            return ErrorFailure();
          }
        }
        ++index;
      }
    }

    m_flags.Mark(k_attributesCached);
    return ErrorSuccess();

  }

  ShaderOperator::uniform_iterator ShaderOperator::
    begin_uniform()
  {
    return m_uniforms.begin();
  }

  ShaderOperator::uniform_iterator ShaderOperator::
    end_uniform()
  {
    return m_uniforms.end();
  }

  ShaderOperator::attribute_iterator ShaderOperator::
    begin_attribute()
  {
    return m_attributes.begin();
  }

  ShaderOperator::attribute_iterator ShaderOperator::
    end_attribute()
  {
    return m_attributes.end();
  }

  //------------------------------------------------------------------------
  // explicit instantiation

  template class tloc::core::smart_ptr::SharedPtr<ShaderOperator>;
  template class tloc::core::Array<UniformPtr>;
  template class tloc::core::Array<AttributePtr>;


};};};