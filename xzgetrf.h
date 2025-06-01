//
// File: xzgetrf.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

#ifndef XZGETRF_H
#define XZGETRF_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
namespace reflapack {
void xzgetrf(int m, int n, ::coder::array<double, 2U> &A, int lda,
             int ipiv_data[], int ipiv_size[2], int *info);

}
} // namespace internal
} // namespace coder

#endif
//
// File trailer for xzgetrf.h
//
// [EOF]
//
