//
// File: bilinear.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

#ifndef BILINEAR_H
#define BILINEAR_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
void bilinear(const ::coder::array<double, 2U> &z, const double p_data[],
              int p_size, const double k_data[], const int k_size[2], double fs,
              ::coder::array<double, 2U> &zd, double pd_data[], int *pd_size,
              double kd_data[], int kd_size[2], double *dd);

}

#endif
//
// File trailer for bilinear.h
//
// [EOF]
//
