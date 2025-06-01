//
// File: buttap.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

// Include Files
#include "buttap.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions
//
// Arguments    : double n
//                creal_T p_data[]
//                int *p_size
//                double *k
// Return Type  : void
//
namespace coder {
void buttap(double n, creal_T p_data[], int *p_size, double *k)
{
  creal_T x_data[1002];
  creal_T ptemp_data[250];
  double y_data[250];
  double im;
  double r;
  int loop_ub;
  int p_tmp;
  int y_size_idx_1;
  if (std::isnan(n - 1.0)) {
    y_size_idx_1 = 1;
    y_data[0] = rtNaN;
  } else if (n - 1.0 < 1.0) {
    y_size_idx_1 = 0;
  } else {
    loop_ub = static_cast<int>(((n - 1.0) - 1.0) / 2.0);
    y_size_idx_1 = loop_ub + 1;
    for (p_tmp = 0; p_tmp <= loop_ub; p_tmp++) {
      y_data[p_tmp] = 2.0 * static_cast<double>(p_tmp) + 1.0;
    }
  }
  im = 2.0 * n;
  for (p_tmp = 0; p_tmp < y_size_idx_1; p_tmp++) {
    r = 3.1415926535897931 * y_data[p_tmp] / im + 1.5707963267948966;
    ptemp_data[p_tmp].re = r * 0.0;
    ptemp_data[p_tmp].im = r;
  }
  for (loop_ub = 0; loop_ub < y_size_idx_1; loop_ub++) {
    im = ptemp_data[loop_ub].im;
    if (im == 0.0) {
      ptemp_data[loop_ub].re = std::exp(ptemp_data[loop_ub].re);
      ptemp_data[loop_ub].im = 0.0;
    } else if (std::isinf(im) && std::isinf(ptemp_data[loop_ub].re) &&
               (ptemp_data[loop_ub].re < 0.0)) {
      ptemp_data[loop_ub].re = 0.0;
      ptemp_data[loop_ub].im = 0.0;
    } else {
      r = std::exp(ptemp_data[loop_ub].re / 2.0);
      ptemp_data[loop_ub].re = r * (r * std::cos(im));
      im = r * (r * std::sin(im));
      ptemp_data[loop_ub].im = im;
    }
  }
  if (std::isnan(n) || std::isinf(n)) {
    r = rtNaN;
  } else if (n == 0.0) {
    r = 0.0;
  } else {
    r = std::fmod(n, 2.0);
    if (r == 0.0) {
      r = 0.0;
    } else if (n < 0.0) {
      r += 2.0;
    }
  }
  if (r == 1.0) {
    *p_size = (y_size_idx_1 << 1) + 1;
    p_data[*p_size - 1].re = -1.0;
    p_data[*p_size - 1].im = 0.0;
  } else {
    *p_size = y_size_idx_1 << 1;
  }
  for (loop_ub = 0; loop_ub < y_size_idx_1; loop_ub++) {
    p_tmp = ((loop_ub + 1) << 1) - 1;
    p_data[p_tmp - 1] = ptemp_data[loop_ub];
    p_data[p_tmp].re = ptemp_data[loop_ub].re;
    p_data[p_tmp].im = -ptemp_data[loop_ub].im;
  }
  for (p_tmp = 0; p_tmp < *p_size; p_tmp++) {
    x_data[p_tmp].re = -p_data[p_tmp].re;
    x_data[p_tmp].im = -p_data[p_tmp].im;
  }
  if (*p_size == 0) {
    *k = 1.0;
  } else {
    *k = x_data[0].re;
    im = x_data[0].im;
    for (loop_ub = 2; loop_ub <= *p_size; loop_ub++) {
      double b_re_tmp;
      double re_tmp;
      re_tmp = x_data[loop_ub - 1].im;
      b_re_tmp = x_data[loop_ub - 1].re;
      r = *k * b_re_tmp - im * re_tmp;
      im = *k * re_tmp + im * b_re_tmp;
      *k = r;
    }
  }
}

} // namespace coder

//
// File trailer for buttap.cpp
//
// [EOF]
//
