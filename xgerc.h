//
// File: xgerc.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

#ifndef XGERC_H
#define XGERC_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
namespace blas {
void xgerc(int m, int n, double alpha1, int ix0, const double y_data[],
           ::coder::array<double, 2U> &A, int ia0, int lda);

}
} // namespace internal
} // namespace coder

#endif
//
// File trailer for xgerc.h
//
// [EOF]
//
