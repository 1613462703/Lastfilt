//
// File: rtGetNaN.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

// Abstract:
//       MATLAB for code generation function to initialize non-finite, NaN
// Include Files
#include "rtGetNaN.h"
#include "rt_nonfinite.h"

// Function: rtGetNaN
// ======================================================================
//  Abstract:
// Initialize rtNaN needed by the generated code.
//  NaN is initialized as non-signaling. Assumes IEEE.
real_T rtGetNaN(void)
{
  return rtNaN;
}

// Function: rtGetNaNF
// =====================================================================
//  Abstract:
//  Initialize rtNaNF needed by the generated code.
//  NaN is initialized as non-signaling. Assumes IEEE
real32_T rtGetNaNF(void)
{
  return rtNaNF;
}

//
// File trailer for rtGetNaN.cpp
//
// [EOF]
//
