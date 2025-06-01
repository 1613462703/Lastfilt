//
// File: qrsolve.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

#ifndef QRSOLVE_H
#define QRSOLVE_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
void qrsolve(const ::coder::array<double, 2U> &A,
             const ::coder::array<double, 2U> &B,
             ::coder::array<double, 2U> &Y);

void qrsolve(const ::coder::array<double, 2U> &A, const double B_data[],
             int B_size, double Y_data[], int *Y_size);

} // namespace internal
} // namespace coder

#endif
//
// File trailer for qrsolve.h
//
// [EOF]
//
