//
// File: div.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

// Include Files
#include "div.h"
#include "lastfilt_data.h"
#include "rt_nonfinite.h"
#include <algorithm>
#include <cmath>

// Function Definitions
//
// Arguments    : creal_T in1_data[]
//                int *in1_size
//                const creal_T in2_data[]
//                const int *in2_size
// Return Type  : void
//
void rdivide(creal_T in1_data[], int *in1_size, const creal_T in2_data[],
             const int *in2_size)
{
  creal_T b_in1_data[1002];
  int b_in1_size;
  int stride_0_0;
  int stride_1_0;
  if (*in2_size == 1) {
    b_in1_size = *in1_size;
  } else {
    b_in1_size = *in2_size;
  }
  stride_0_0 = (*in1_size != 1);
  stride_1_0 = (*in2_size != 1);
  if (*in2_size != 1) {
    *in1_size = *in2_size;
  }
  for (int i{0}; i < *in1_size; i++) {
    double ai;
    double ar;
    double bi;
    double br;
    int ar_tmp;
    ar_tmp = i * stride_0_0;
    ar = in1_data[ar_tmp].re;
    ai = in1_data[ar_tmp].im;
    ar_tmp = i * stride_1_0;
    br = in2_data[ar_tmp].re;
    bi = in2_data[ar_tmp].im;
    if (bi == 0.0) {
      if (ai == 0.0) {
        b_in1_data[i].re = ar / br;
        b_in1_data[i].im = 0.0;
      } else if (ar == 0.0) {
        b_in1_data[i].re = 0.0;
        b_in1_data[i].im = ai / br;
      } else {
        b_in1_data[i].re = ar / br;
        b_in1_data[i].im = ai / br;
      }
    } else if (br == 0.0) {
      if (ar == 0.0) {
        b_in1_data[i].re = ai / bi;
        b_in1_data[i].im = 0.0;
      } else if (ai == 0.0) {
        b_in1_data[i].re = 0.0;
        b_in1_data[i].im = -(ar / bi);
      } else {
        b_in1_data[i].re = ai / bi;
        b_in1_data[i].im = -(ar / bi);
      }
    } else {
      double bim;
      double brm;
      brm = std::abs(br);
      bim = std::abs(bi);
      if (brm > bim) {
        double s;
        s = bi / br;
        bim = br + s * bi;
        b_in1_data[i].re = (ar + s * ai) / bim;
        b_in1_data[i].im = (ai - s * ar) / bim;
      } else if (bim == brm) {
        double s;
        if (br > 0.0) {
          s = 0.5;
        } else {
          s = -0.5;
        }
        if (bi > 0.0) {
          bim = 0.5;
        } else {
          bim = -0.5;
        }
        b_in1_data[i].re = (ar * s + ai * bim) / brm;
        b_in1_data[i].im = (ai * s - ar * bim) / brm;
      } else {
        double s;
        s = br / bi;
        bim = bi + s * br;
        b_in1_data[i].re = (s * ar + ai) / bim;
        b_in1_data[i].im = (s * ai - ar) / bim;
      }
    }
  }
  *in1_size = b_in1_size;
  if (b_in1_size - 1 >= 0) {
    std::copy(&b_in1_data[0], &b_in1_data[b_in1_size], &in1_data[0]);
  }
}

//
// File trailer for div.cpp
//
// [EOF]
//
