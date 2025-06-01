//
// File: mldivide.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

// Include Files
#include "mldivide.h"
#include "lusolve.h"
#include "qrsolve.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <algorithm>
#include <cstring>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &A
//                const ::coder::array<double, 2U> &B
//                ::coder::array<double, 2U> &Y
// Return Type  : void
//
namespace coder {
void mldivide(const ::coder::array<double, 2U> &A,
              const ::coder::array<double, 2U> &B,
              ::coder::array<double, 2U> &Y)
{
  if ((A.size(0) == 0) || (A.size(1) == 0) ||
      ((B.size(0) == 0) || (B.size(1) == 0))) {
    int loop_ub;
    Y.set_size(A.size(1), B.size(1));
    loop_ub = A.size(1) * B.size(1);
    for (int i{0}; i < loop_ub; i++) {
      Y[i] = 0.0;
    }
  } else if (A.size(0) == A.size(1)) {
    int loop_ub;
    Y.set_size(B.size(0), B.size(1));
    loop_ub = B.size(0) * B.size(1);
    for (int i{0}; i < loop_ub; i++) {
      Y[i] = B[i];
    }
    internal::lusolve(A, Y);
  } else {
    internal::qrsolve(A, B, Y);
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &A
//                const double B_data[]
//                int B_size
//                double Y_data[]
//                int *Y_size
// Return Type  : void
//
void mldivide(const ::coder::array<double, 2U> &A, const double B_data[],
              int B_size, double Y_data[], int *Y_size)
{
  if ((A.size(0) == 0) || (A.size(1) == 0) || (B_size == 0)) {
    int loop_ub;
    *Y_size = A.size(1);
    loop_ub = A.size(1);
    if (loop_ub - 1 >= 0) {
      std::memset(&Y_data[0], 0,
                  static_cast<unsigned int>(loop_ub) * sizeof(double));
    }
  } else if (A.size(0) == A.size(1)) {
    *Y_size = B_size;
    std::copy(&B_data[0], &B_data[B_size], &Y_data[0]);
    internal::lusolve(A, Y_data, Y_size);
  } else {
    internal::qrsolve(A, B_data, B_size, Y_data, Y_size);
  }
}

} // namespace coder

//
// File trailer for mldivide.cpp
//
// [EOF]
//
