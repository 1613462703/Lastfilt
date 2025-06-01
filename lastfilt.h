//
// File: lastfilt.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

#ifndef LASTFILT_H
#define LASTFILT_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void lastfilt(const double x[50001], double fs, double fc_low,
                     double fc_high, double N, const char filterType_data[],
                     const int filterType_size, double y[50001]);

#endif
//
// File trailer for lastfilt.h
//
// [EOF]
//
