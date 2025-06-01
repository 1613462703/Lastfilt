//
// File: filter.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

#ifndef FILTER_H
#define FILTER_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
void filter(const double b_data[], const int b_size[2], const double a_data[],
            const int a_size[2], const double x[], double y[]);

}

#endif
//
// File trailer for filter.h
//
// [EOF]
//
