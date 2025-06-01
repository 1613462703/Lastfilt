//
// File: xgetrf.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

// Include Files
#include "xgetrf.h"
#include "rt_nonfinite.h"
#include "xzgetrf.h"
#include "coder_array.h"
#include <algorithm>

// Function Definitions
//
// Arguments    : int m
//                int n
//                ::coder::array<double, 2U> &A
//                int lda
//                int ipiv_data[]
//                int ipiv_size[2]
// Return Type  : void
//
namespace coder {
namespace internal {
namespace lapack {
void xgetrf(int m, int n, ::coder::array<double, 2U> &A, int lda,
            int ipiv_data[], int ipiv_size[2])
{
  array<double, 2U> b_A;
  int b_ipiv_data[1002];
  int b_ipiv_size[2];
  int loop_ub;
  b_A.set_size(A.size(0), A.size(1));
  loop_ub = A.size(0) * A.size(1);
  for (int i{0}; i < loop_ub; i++) {
    b_A[i] = A[i];
  }
  reflapack::xzgetrf(m, n, b_A, lda, b_ipiv_data, b_ipiv_size, &loop_ub);
  A.set_size(b_A.size(0), b_A.size(1));
  loop_ub = b_A.size(1);
  for (int i{0}; i < loop_ub; i++) {
    int b_loop_ub;
    b_loop_ub = b_A.size(0);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
      A[i1 + A.size(0) * i] = b_A[i1 + b_A.size(0) * i];
    }
  }
  ipiv_size[0] = 1;
  ipiv_size[1] = b_ipiv_size[1];
  loop_ub = b_ipiv_size[1];
  if (loop_ub - 1 >= 0) {
    std::copy(&b_ipiv_data[0], &b_ipiv_data[loop_ub], &ipiv_data[0]);
  }
}

} // namespace lapack
} // namespace internal
} // namespace coder

//
// File trailer for xgetrf.cpp
//
// [EOF]
//
