#include "tlocImage.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/containers/tlocContainers.inl.h>
#include <tlocCore/utilities/tlocContainerUtils.h>

namespace tloc { namespace graphics { namespace media {

  namespace
  {
    enum
    {
      width = types::dimension::width,
      height = types::dimension::height,
    };
  };

  Image::Image()
    : m_dim(0)
  {
  }

  Image::error_type
    Image::LoadFromMemory(const_uchar8_ptr a_buffer, dimension_type a_dim,
                          size_type a_channels)
  {
    if ( (a_buffer == nullptr) || a_dim[0] == 0 || a_dim[1] == 0 ||
         (a_channels == 0) )
    { return TLOC_ERROR(common_error_types::error_no_data); }

    // Check if a_size can accommodate a whole number of Color*
    TLOC_ASSERT( ((a_channels % sizeof(color_type)) == 0),
      "The buffer has an invalid size!");

    const color_type* buffer = reinterpret_cast<const color_type*>(a_buffer.get());
    m_pixels.assign(buffer, buffer + (a_dim[0] * a_dim[1]));

    m_dim = a_dim;

    return ErrorSuccess;
  }

  Image::error_type
    Image::
    LoadFromMemory(const pixel_container_type& a_buffer, dimension_type a_dim)
  {
    TLOC_ASSERT( (a_dim[0] * a_dim[1]) == a_buffer.size(),
      "Invalid buffer size wrt image dimensions");
    m_pixels = a_buffer;
    m_dim = a_dim;
    return ErrorSuccess;
  }

  Image::error_type
    Image::
    DoLoadFromImages(const image_ptr_cont& a_arrayOfImages)
  {
    TLOC_ASSERT_WIP();
    TLOC_UNUSED(a_arrayOfImages);
    return ErrorSuccess;
  }

  Image::error_type
    Image::Create(dimension_type a_dim, const color_type& a_color)
  {
    m_dim = a_dim;

    m_pixels.clear();
    m_pixels.resize(m_dim[width] * m_dim[height] , a_color);

    return ErrorSuccess;
  }

  void Image::SetPixel(size_type a_X, size_type a_Y, const color_type& a_color)
  {
    tl_int index = core_utils::GetIndex(m_dim, core_ds::MakeTuple(a_X, a_Y));
    m_pixels[index] = a_color;
  }

  Image::error_type
    Image::
    AddPadding(dimension_type a_padding, const color_type& a_color)
  {
    dimension_type a_paddingTotal = core_ds::Add(a_padding, a_padding);
    dimension_type newDim = core_ds::MakeTuple
      (m_dim[0] + a_paddingTotal[0], m_dim[1] + a_paddingTotal[1]);

    pixel_container_type newImg(newDim[0] * newDim[1]);

    for (size_type y = 0; y < newDim[1]; ++y)
    {
      for (size_type x = 0; x < newDim[0]; ++x)
      {
        tl_int index = core_utils::GetIndex(newDim, core_ds::MakeTuple(x, y));

        if (x < a_padding[0] || x > m_dim[0] ||
            y < a_padding[1] || y > m_dim[1])
        {
          newImg[index] = a_color;
        }
        else
        {
          tl_int currImgIndex = core_utils::GetIndex
            (m_dim, core_ds::MakeTuple(x - a_padding[0],
                                       y - a_padding[1]));

          newImg[index] = m_pixels[currImgIndex];
        }
      }
    }

    this_type temp;
    error_type err = temp.LoadFromMemory(newImg, newDim);

    if (err.Failed())
    { return err; }

    core::swap(temp, *this);
    return ErrorSuccess;
  }

  const Image::color_type&  Image::GetPixel(size_type a_X, size_type a_Y) const
  {
    tl_int index = core_utils::GetIndex(m_dim, core_ds::MakeTuple(a_X, a_Y));
    return m_pixels[index];
  }

};};};

//------------------------------------------------------------------------
// Explicitly instantiate the container

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_med;
using namespace tloc::gfx_t;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Image);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(Color);