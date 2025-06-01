//
// File: xzhgeqz.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

#ifndef XZHGEQZ_H
#define XZHGEQZ_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
namespace reflapack {
void xzhgeqz(const ::coder::array<creal_T, 2U> &A, int ilo, int ihi, int *info,
             creal_T alpha1_data[], int *alpha1_size, creal_T beta1_data[],
             int *beta1_size);

}
} // namespace internal
} // namespace coder

#endif
//
// File trailer for xzhgeqz.h
//
// [EOF]
//
