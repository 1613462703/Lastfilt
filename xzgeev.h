//
// File: xzgeev.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

#ifndef XZGEEV_H
#define XZGEEV_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
namespace reflapack {
void xzgeev(const ::coder::array<double, 2U> &A, int *info,
            creal_T alpha1_data[], int *alpha1_size, creal_T beta1_data[],
            int *beta1_size);

}
} // namespace internal
} // namespace coder

#endif
//
// File trailer for xzgeev.h
//
// [EOF]
//
