//
// File: filter.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

// Include Files
#include "filter.h"
#include "rt_nonfinite.h"
#include <algorithm>
#include <cmath>
#include <cstring>

// Function Definitions
//
// Arguments    : const double b_data[]
//                const int b_size[2]
//                const double a_data[]
//                const int a_size[2]
//                const double x[50001]
//                double y[50001]
// Return Type  : void
//
namespace coder {
void filter(const double b_data[], const int b_size[2], const double a_data[],
            const int a_size[2], const double x[], double y[])
{
  double b_b_data[2003];
  double b_a_data[1003];
  double a1;
  int loop_ub;
  int na;
  int nb;
  loop_ub = b_size[1];
  if (loop_ub - 1 >= 0) {
    std::copy(&b_data[0], &b_data[loop_ub], &b_b_data[0]);
  }
  loop_ub = a_size[1];
  if (loop_ub - 1 >= 0) {
    std::copy(&a_data[0], &a_data[loop_ub], &b_a_data[0]);
  }
  na = a_size[1];
  nb = b_size[1];
  a1 = a_data[0];
  if ((!std::isinf(a_data[0])) && (!std::isnan(a_data[0])) &&
      (!(a_data[0] == 0.0)) && (a_data[0] != 1.0)) {
    for (int k{0}; k < nb; k++) {
      b_b_data[k] /= a1;
    }
    for (int k{2}; k <= na; k++) {
      b_a_data[k - 1] /= a1;
    }
    b_a_data[0] = 1.0;
  }
  std::memset(&y[0], 0, 50001U * sizeof(double));
  if (a_size[1] == 1) {
    for (int k{0}; k < nb; k++) {
      loop_ub = k + 1;
      for (int j{loop_ub}; j < 50002; j++) {
        y[j - 1] += b_b_data[k] * x[(j - k) - 1];
      }
    }
  } else {
    for (int k{0}; k < 50001; k++) {
      int u0;
      int y_tmp;
      u0 = 50001 - k;
      if (u0 > nb) {
        u0 = nb;
      }
      for (int j{0}; j < u0; j++) {
        y_tmp = k + j;
        y[y_tmp] += x[k] * b_b_data[j];
      }
      a1 = -y[k];
      u0 = 50000 - k;
      loop_ub = na - 1;
      if (u0 <= loop_ub) {
        loop_ub = u0;
      }
      loop_ub = static_cast<unsigned short>(loop_ub);
      for (int j{0}; j < loop_ub; j++) {
        y_tmp = (k + j) + 1;
        y[y_tmp] += a1 * b_a_data[j + 1];
      }
    }
  }
}

} // namespace coder

//
// File trailer for filter.cpp
//
// [EOF]
//
