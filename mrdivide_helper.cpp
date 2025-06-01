//
// File: mrdivide_helper.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

// Include Files
#include "mrdivide_helper.h"
#include "lusolve.h"
#include "qrsolve.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <algorithm>
#include <cstring>

// Function Definitions
//
// Arguments    : const double A_data[]
//                const int A_size[2]
//                const ::coder::array<double, 2U> &B
//                double Y_data[]
//                int Y_size[2]
// Return Type  : void
//
namespace coder {
namespace internal {
void mrdiv(const double A_data[], const int A_size[2],
           const ::coder::array<double, 2U> &B, double Y_data[], int Y_size[2])
{
  array<double, 2U> b_B;
  double b_A_data[1002];
  double tmp_data[1002];
  int loop_ub;
  if ((A_size[1] == 0) || ((B.size(0) == 0) || (B.size(1) == 0))) {
    Y_size[0] = 1;
    Y_size[1] = B.size(0);
    loop_ub = B.size(0);
    if (loop_ub - 1 >= 0) {
      std::memset(&Y_data[0], 0,
                  static_cast<unsigned int>(loop_ub) * sizeof(double));
    }
  } else if (B.size(0) == B.size(1)) {
    Y_size[0] = 1;
    Y_size[1] = A_size[1];
    loop_ub = A_size[1];
    std::copy(&A_data[0], &A_data[loop_ub], &Y_data[0]);
    b_lusolve(B, Y_data, Y_size);
  } else {
    int b_loop_ub;
    b_B.set_size(B.size(1), B.size(0));
    loop_ub = B.size(0);
    b_loop_ub = B.size(1);
    for (int i{0}; i < loop_ub; i++) {
      for (int i1{0}; i1 < b_loop_ub; i1++) {
        b_B[i1 + b_B.size(0) * i] = B[i + B.size(0) * i1];
      }
    }
    loop_ub = A_size[1];
    std::copy(&A_data[0], &A_data[loop_ub], &b_A_data[0]);
    qrsolve(b_B, b_A_data, A_size[1], tmp_data, &loop_ub);
    Y_size[0] = 1;
    Y_size[1] = loop_ub;
    if (loop_ub - 1 >= 0) {
      std::copy(&tmp_data[0], &tmp_data[loop_ub], &Y_data[0]);
    }
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for mrdivide_helper.cpp
//
// [EOF]
//
