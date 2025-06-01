//
// File: lusolve.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

#ifndef LUSOLVE_H
#define LUSOLVE_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
void b_lusolve(const ::coder::array<double, 2U> &A, double B_data[],
               const int B_size[2]);

void lusolve(const ::coder::array<double, 2U> &A,
             ::coder::array<double, 2U> &B);

void lusolve(const ::coder::array<double, 2U> &A, double B_data[],
             const int *B_size);

} // namespace internal
} // namespace coder

#endif
//
// File trailer for lusolve.h
//
// [EOF]
//
