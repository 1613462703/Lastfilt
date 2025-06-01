//
// File: butter.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

#ifndef BUTTER_H
#define BUTTER_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
void b_butter(double n, double Wn, double varargout_1_data[],
              int varargout_1_size[2], double varargout_2_data[],
              int varargout_2_size[2]);

void b_butter(double n, const double Wn[2], double varargout_1_data[],
              int varargout_1_size[2], double varargout_2_data[],
              int varargout_2_size[2]);

void butter(double n, double Wn, double varargout_1_data[],
            int varargout_1_size[2], double varargout_2_data[],
            int varargout_2_size[2]);

void butter(double n, const double Wn[2], double varargout_1_data[],
            int varargout_1_size[2], double varargout_2_data[],
            int varargout_2_size[2]);

} // namespace coder

#endif
//
// File trailer for butter.h
//
// [EOF]
//
