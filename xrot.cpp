//
// File: xrot.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

// Include Files
#include "xrot.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : int n
//                ::coder::array<double, 2U> &x
//                int ix0
//                int incx
//                int iy0
//                int incy
//                double c
//                double s
// Return Type  : void
//
namespace coder {
namespace internal {
namespace blas {
void xrot(int n, ::coder::array<double, 2U> &x, int ix0, int incx, int iy0,
          int incy, double c, double s)
{
  if (n >= 1) {
    int i;
    i = static_cast<unsigned short>(n);
    for (int k{0}; k < i; k++) {
      double temp;
      int b_temp_tmp;
      int temp_tmp;
      temp_tmp = (iy0 + k * incx) - 1;
      b_temp_tmp = (ix0 + k * incy) - 1;
      temp = c * x[b_temp_tmp] + s * x[temp_tmp];
      x[temp_tmp] = c * x[temp_tmp] - s * x[b_temp_tmp];
      x[b_temp_tmp] = temp;
    }
  }
}

//
// Arguments    : int n
//                ::coder::array<double, 2U> &x
//                int ix0
//                int iy0
//                double c
//                double s
// Return Type  : void
//
void xrot(int n, ::coder::array<double, 2U> &x, int ix0, int iy0, double c,
          double s)
{
  if (n >= 1) {
    int i;
    i = static_cast<unsigned short>(n);
    for (int k{0}; k < i; k++) {
      double temp;
      int b_temp_tmp;
      int temp_tmp;
      temp_tmp = (iy0 + k) - 1;
      b_temp_tmp = (ix0 + k) - 1;
      temp = c * x[b_temp_tmp] + s * x[temp_tmp];
      x[temp_tmp] = c * x[temp_tmp] - s * x[b_temp_tmp];
      x[b_temp_tmp] = temp;
    }
  }
}

} // namespace blas
} // namespace internal
} // namespace coder

//
// File trailer for xrot.cpp
//
// [EOF]
//
