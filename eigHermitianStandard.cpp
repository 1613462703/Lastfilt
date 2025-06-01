//
// File: eigHermitianStandard.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

// Include Files
#include "eigHermitianStandard.h"
#include "rt_nonfinite.h"
#include "schur.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &A
//                double V_data[]
//                int *V_size
// Return Type  : void
//
namespace coder {
void eigHermitianStandard(const ::coder::array<double, 2U> &A, double V_data[],
                          int *V_size)
{
  array<double, 2U> T;
  array<double, 2U> b_A;
  int n;
  b_A.set_size(A.size(0), A.size(1));
  n = A.size(0) * A.size(1) - 1;
  for (int k{0}; k <= n; k++) {
    b_A[k] = A[k];
  }
  schur(b_A, T);
  n = T.size(0);
  *V_size = T.size(0);
  for (int k{0}; k < n; k++) {
    V_data[k] = T[k + T.size(0) * k];
  }
}

} // namespace coder

//
// File trailer for eigHermitianStandard.cpp
//
// [EOF]
//
