#include "tlocOpenGL.h"

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tlocContainers.inl.h>
#include <tlocCore/platform/tlocPlatform.h>
#include <tlocCore/logging/tlocLogger.h>

#include <tlocGraphics/opengl/tlocError.h>
#include <tlocGraphics/error/tlocErrorTypes.h>
#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/window/tlocWindow.h>

#if defined(TLOC_OS_WIN)
# include <tlocGraphics/opengl/tlocOpenGLExt.h>
#endif

namespace tloc { namespace graphics { namespace gl {

  // -----------------------------------------------------------------------
  // common typedefs

  typedef core_err::Error           error_type;

  // ///////////////////////////////////////////////////////////////////////
  // OpenGL get functions

  namespace p_get
  {
    namespace priv
    {
      void DoGet(GLint& a_out, const GLint s_glParamName)
      {
        glGetIntegerv(s_glParamName, &a_out);
      }

      void DoGet(GLint*& a_out, const GLint s_glParamName)
      {
        glGetIntegerv(s_glParamName, a_out);
      }

      void DoGet(GLfloat&		a_out, const GLint s_glParamName)
      {
        glGetFloatv(s_glParamName, &a_out);
      }

      void DoGet(GLfloat*&	a_out, const GLint s_glParamName)
      {
        glGetFloatv(s_glParamName, a_out);
      }

#if defined (TLOC_OS_WIN) // TODO: Change to TLOC_GFX_PLATFORM_GL
      void DoGet(GLdouble&	a_out, const GLint s_glParamName)
      {
        glGetDoublev(s_glParamName, &a_out);
      }

      void DoGet(GLdouble*&	a_out, const GLint s_glParamName)
      {
        glGetDoublev(s_glParamName, a_out);
      }
#endif
    };

    // -----------------------------------------------------------------------
    // static definitions

    const GLint CurrentProgram::s_glParamName               = GL_CURRENT_PROGRAM;
    const GLint MaxCombinedTextureImageUnits::s_glParamName = GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS;
    const GLint MaxVertexAttribs::s_glParamName             = GL_MAX_VERTEX_ATTRIBS;

#if defined (TLOC_OS_WIN)
    const GLint NumExtensions::s_glParamName                = GL_NUM_EXTENSIONS;
    const GLint NumShadingLanguageVersions::s_glParamName   = GL_NUM_SHADING_LANGUAGE_VERSIONS;
#endif
  };

  // ///////////////////////////////////////////////////////////////////////
  // VertexAttribArrays

  namespace vertex_attrib_array {

    using namespace gfx_t;

    // -----------------------------------------------------------------------

    namespace {
      core_conts::Array<gl_int, core_conts::Array_Unordered> g_enabledAttributes;
    };

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    bool 
      Enable(gl_int a_index)
    {
      if (IsEnabled(a_index) == false)
      { 
        g_enabledAttributes.push_back(a_index);
        glEnableVertexAttribArray(a_index);
        return true;
      }
      else
      {
        TLOC_LOG_GFX_WARN() << "VertexAttribArray(" << a_index << ")"
          << " already enabled";
        return false;
      }
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    bool
      EnableIfDisabled(gfx_t::gl_int a_index)
    {
      if (IsEnabled(a_index))
      { return false; }
      else
      { return Enable(a_index); }
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    bool 
      IsEnabled(gfx_t::gl_int a_index)
    { 
      return core::find_all(g_enabledAttributes, a_index) != 
                            g_enabledAttributes.end();
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    bool 
      Disable(gfx_t::gl_int a_index)
    {
      if (IsEnabled(a_index))
      { 
        g_enabledAttributes.erase
          (core::remove_all(g_enabledAttributes, a_index), 
                            g_enabledAttributes.end());

        glDisableVertexAttribArray(a_index);
        return true;
      }
      else
      {
        TLOC_LOG_GFX_WARN() << "VertexAttribArray(" << a_index << ")"
          << " already disabled";
        return false;
      }
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    void
      DisableAll()
    { 
      while(g_enabledAttributes.empty() == false)
      { Disable(g_enabledAttributes.back()); }
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    void
      ForceDisableAll()
    {
      DisableAll();

      // now disable ALL gl vertex attrib arrays
      gl_int maxAttribs = 
        core_utils::CastNumber<gl_int>(g_enabledAttributes.size());

      for (gl_int i = 0; i < maxAttribs; ++i)
      { glDisableVertexAttribArray(i); }
    }

  };
  
  // ///////////////////////////////////////////////////////////////////////
  // VertexArrayObject
  
  namespace vertex_array_object {
    
    void
      Bind(gfx_t::gl_uint a_name)
    {
#ifdef TLOC_OS_IPHONE
      glBindVertexArrayOES(a_name);
#else
      glBindVertexArray(a_name);
#endif
    }
    
    void
      UnBind()
    {
      Bind(0);
    }
    
    gfx_t::gl_uint
      Generate()
    {
      gfx_t::gl_uint handle;
#ifdef TLOC_OS_IPHONE
      glGenVertexArraysOES(1, &handle);
#else
      glGenVertexArrays(1, &handle);
#endif
      return handle;
    }
    
    void
      Destroy(gfx_t::gl_uint a_name)
    {
#ifdef TLOC_OS_IPHONE
      glDeleteVertexArraysOES(1, &a_name);
#else
      glDeleteVertexArrays(1, &a_name);
#endif
    }
    
  }

  // ///////////////////////////////////////////////////////////////////////
  // Texture units

  namespace
  {
    typedef core_conts::tl_array<GLint>::type   gl_int_array;

    typedef core_conts::tl_array<GLint>::type   gl_int_array;

    GLint         g_maxTextureUnits = -1;
    GLint         g_currentAvailableTextureUnit = 0;
    gl_int_array  g_availableTextureUnits;

    void DoSetMaxTextureUnits()
    {
      g_maxTextureUnits = Get<p_get::MaxCombinedTextureImageUnits>();

      g_availableTextureUnits.reserve(g_maxTextureUnits);

      for (int i = 0; i < g_maxTextureUnits; ++i)
      {
        g_availableTextureUnits.push_back(GL_TEXTURE0 + i);
      }
    }
  }

  // ///////////////////////////////////////////////////////////////////////
  // Texture image unit functions
  // For clarification on Texture image units and Texture units:
  // http://www.opengl.org/wiki/Sampler_(GLSL)

  core_err::Error
    GetNextAvailableTextureImageUnit(GLint& a_texImgUnitOut)
  {
    if (g_maxTextureUnits != -1)
    {
      if (g_maxTextureUnits == 0)
      { return TLOC_ERROR(error::error_no_texture_units_available); }

      if (g_currentAvailableTextureUnit == g_maxTextureUnits)
      { g_currentAvailableTextureUnit = 0; }

      a_texImgUnitOut = g_availableTextureUnits[g_currentAvailableTextureUnit];
      ++g_currentAvailableTextureUnit;

      return ErrorSuccess;
    }

    DoSetMaxTextureUnits();
    return GetNextAvailableTextureImageUnit(a_texImgUnitOut);
  }

  void
    ActivateTextureImageUnit(GLint a_texImgUnit)
  {
    if (g_maxTextureUnits != -1)
    {
      TLOC_ASSERT_LOW_LEVEL(IsValidTextureImageUnit(a_texImgUnit), "Invalid texture unit");

      glActiveTexture(a_texImgUnit);
      gl::Error err; TLOC_UNUSED(err);
      TLOC_ASSERT(err.Succeeded(), "glActiveTexture() failed");
      return;
    }

    DoSetMaxTextureUnits();
    ActivateTextureImageUnit(a_texImgUnit);
  }

  bool
    IsValidTextureImageUnit(GLint a_texImgUnit)
  {
    return a_texImgUnit >= GL_TEXTURE0 &&
           a_texImgUnit < GL_TEXTURE0 + g_maxTextureUnits;
  }

  // ///////////////////////////////////////////////////////////////////////
  // Texture Unit functions

  bool
    IsValidTextureUnit(GLint a_texUnit)
  {
    return a_texUnit < g_maxTextureUnits;
  }

  GLint
    GetTextureUnitFromTextureImageUnit(GLint a_texImgUnit)
  {
    TLOC_ASSERT(IsValidTextureImageUnit(a_texImgUnit), "Invalid texture image unit");

    return a_texImgUnit - GL_TEXTURE0;
  }
  
  // ///////////////////////////////////////////////////////////////////////
  // InitializePlatform

  namespace {

#if defined(TLOC_WIN32) || defined(TLOC_WIN64)
    static bool g_platformInitialized = false;
#else
    // nothing needs to be done on other platforms
    static bool g_platformInitialized = true;
#endif

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T_Platform>
    bool
      DoIsPlatformInitialized(T_Platform)
    { return g_platformInitialized; }
    
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T_Platform>
    core_err::Error
      DoInitializePlatform(T_Platform)
    { return ErrorSuccess; }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#if defined(TLOC_WIN32) || defined(TLOC_WIN64)

    bool
      DoIsPlatformInitialized(core_plat::p_platform_info::win)
    { return gl::OpenGLExt::IsInitialized(); }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    core_err::Error
      DoInitializePlatform(core_plat::p_platform_info::win)
    {
      if (g_platformInitialized == false)
      {
        error_type res = gl::OpenGLExt::Initialize();
        if (res != common_error_types::error_initialize)
        { return res; }

        g_platformInitialized = true;
        return TLOC_ERROR(common_error_types::error_success);
      }

      return TLOC_ERROR(common_error_types::error_already_initialized);
    }

#endif

  };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void DoInitializeInternalVariables()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  core_err::Error
    InitializePlatform()
  {
    AssertOpenGLContextExists();

    core_err::Error err = ErrorSuccess;
    
    if ( DoIsPlatformInitialized(core_plat::PlatformInfo::platform_type()) == false)
    { err = DoInitializePlatform(core_plat::PlatformInfo::platform_type()); }

    if (err.Succeeded())
    {
      g_platformInitialized = true;

      TLOC_LOG_GFX_INFO_NO_FILENAME() << "-------------- GFX Platform Info --------------";
      TLOC_LOG_GFX_INFO_NO_FILENAME() << "OpenGL Version: " << (const char*)glGetString(GL_VERSION);
      TLOC_LOG_GFX_INFO_NO_FILENAME() << "GLSL Version: " << (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
      TLOC_LOG_GFX_INFO_NO_FILENAME() << "Vendor: " << (const char*)glGetString(GL_VENDOR);
      TLOC_LOG_GFX_INFO_NO_FILENAME() << "Hardware: " << (const char*)glGetString(GL_RENDERER);
      TLOC_LOG_GFX_INFO_NO_FILENAME() << "Total VertexAttribArrays: " << Get<p_get::MaxVertexAttribs>();
      TLOC_LOG_GFX_INFO_NO_FILENAME() << "Total TextureUnits: " << Get<p_get::MaxCombinedTextureImageUnits>();
      TLOC_LOG_GFX_INFO_NO_FILENAME() << "-----------------------------------------------";

      // internal variables that need a one time setup
      DoInitializeInternalVariables();

      return ErrorSuccess;
    }
    else
    {
      g_platformInitialized = false;
      return err;
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    IsPlatformInitialized()
  {
    return g_platformInitialized;
  }
  
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    AssertOpenGLContextExists()
  {
    TLOC_ASSERT(gfx_win::GetCurrentActiveWindow() ?
                gfx_win::GetCurrentActiveWindow()->HasValidContext() :
                false,
                "No OpenGL context exists (destroyed?) OR no existing context "
                "has been set as active");
  }

};};};