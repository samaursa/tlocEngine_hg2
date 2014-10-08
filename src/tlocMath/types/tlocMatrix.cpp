#include "tlocMatrix.h"

#define TLOC_MATRIX_ALLOW_EASY_OPERATIONS
#include "tlocMatrix.opt.inl.h"

namespace tloc { namespace math { namespace types {

#include "tlocMatrixExplicitMacros.h"
  TLOC_EXPLICITLY_INSTANTIATE_MATRIX(f32, 2);
  TLOC_EXPLICITLY_INSTANTIATE_MATRIX(f32, 3);
  TLOC_EXPLICITLY_INSTANTIATE_MATRIX(f32, 4);

  TLOC_EXPLICITLY_INSTANTIATE_MATRIX(f64, 2);
  TLOC_EXPLICITLY_INSTANTIATE_MATRIX(f64, 3);
  TLOC_EXPLICITLY_INSTANTIATE_MATRIX(f64, 4);

};};};