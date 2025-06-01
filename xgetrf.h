//
// File: xgetrf.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

#ifndef XGETRF_H
#define XGETRF_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
namespace lapack {
void xgetrf(int m, int n, ::coder::array<double, 2U> &A, int lda,
            int ipiv_data[], int ipiv_size[2]);

}
} // namespace internal
} // namespace coder

#endif
//
// File trailer for xgetrf.h
//
// [EOF]
//
