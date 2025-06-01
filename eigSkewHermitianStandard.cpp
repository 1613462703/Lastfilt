//
// File: eigSkewHermitianStandard.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

// Include Files
#include "eigSkewHermitianStandard.h"
#include "rt_nonfinite.h"
#include "schur.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &A
//                creal_T V_data[]
//                int *V_size
// Return Type  : void
//
namespace coder {
void eigSkewHermitianStandard(const ::coder::array<double, 2U> &A,
                              creal_T V_data[], int *V_size)
{
  array<double, 2U> T;
  array<double, 2U> b_A;
  int i;
  int n;
  b_A.set_size(A.size(0), A.size(1));
  n = A.size(0) * A.size(1) - 1;
  for (i = 0; i <= n; i++) {
    b_A[i] = A[i];
  }
  schur(b_A, T);
  n = T.size(0);
  *V_size = T.size(0);
  i = 1;
  int exitg1;
  do {
    exitg1 = 0;
    if (i <= n) {
      boolean_T guard1{false};
      guard1 = false;
      if (i != n) {
        double lambda;
        lambda = T[i + T.size(0) * (i - 1)];
        if (lambda != 0.0) {
          lambda = std::abs(lambda);
          V_data[i - 1].re = 0.0;
          V_data[i - 1].im = lambda;
          V_data[i].re = 0.0;
          V_data[i].im = -lambda;
          i += 2;
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }
      if (guard1) {
        V_data[i - 1].re = 0.0;
        V_data[i - 1].im = 0.0;
        i++;
      }
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);
}

} // namespace coder

//
// File trailer for eigSkewHermitianStandard.cpp
//
// [EOF]
//
