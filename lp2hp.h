//
// File: lp2hp.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

#ifndef LP2HP_H
#define LP2HP_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
void lp2hp(const ::coder::array<double, 2U> &a, const double b_data[],
           int b_size, const double c_data[], const int c_size[2], double d,
           double wo, ::coder::array<double, 2U> &at, double bt_data[],
           int *bt_size, double ct_data[], int ct_size[2], double *dt);

}

#endif
//
// File trailer for lp2hp.h
//
// [EOF]
//
