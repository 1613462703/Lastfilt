//
// File: xgeqp3.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

#ifndef XGEQP3_H
#define XGEQP3_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
namespace lapack {
void xgeqp3(::coder::array<double, 2U> &A, double tau_data[], int *tau_size,
            int jpvt_data[], int jpvt_size[2]);

}
} // namespace internal
} // namespace coder

#endif
//
// File trailer for xgeqp3.h
//
// [EOF]
//
