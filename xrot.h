//
// File: xrot.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

#ifndef XROT_H
#define XROT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
namespace blas {
void xrot(int n, ::coder::array<double, 2U> &x, int ix0, int incx, int iy0,
          int incy, double c, double s);

void xrot(int n, ::coder::array<double, 2U> &x, int ix0, int iy0, double c,
          double s);

} // namespace blas
} // namespace internal
} // namespace coder

#endif
//
// File trailer for xrot.h
//
// [EOF]
//
