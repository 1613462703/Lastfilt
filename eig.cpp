//
// File: eig.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

// Include Files
#include "eig.h"
#include "div.h"
#include "eigHermitianStandard.h"
#include "eigSkewHermitianStandard.h"
#include "lastfilt_data.h"
#include "rt_nonfinite.h"
#include "xzgeev.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &A
//                creal_T V_data[]
//                int *V_size
// Return Type  : void
//
namespace coder {
void eig(const ::coder::array<double, 2U> &A, creal_T V_data[], int *V_size)
{
  creal_T beta1_data[1002];
  double tmp_data[1002];
  int k;
  int nx;
  *V_size = A.size(0);
  if ((A.size(0) != 0) && (A.size(1) != 0)) {
    boolean_T p;
    nx = A.size(0) * A.size(1);
    p = true;
    for (k = 0; k < nx; k++) {
      if ((!p) || (std::isinf(A[k]) || std::isnan(A[k]))) {
        p = false;
      }
    }
    if (!p) {
      *V_size = A.size(0);
      nx = A.size(0);
      for (k = 0; k < nx; k++) {
        V_data[k].re = rtNaN;
        V_data[k].im = 0.0;
      }
    } else {
      int exitg1;
      boolean_T exitg2;
      p = (A.size(0) == A.size(1));
      if (p) {
        nx = 0;
        exitg2 = false;
        while ((!exitg2) && (nx <= A.size(1) - 1)) {
          k = 0;
          do {
            exitg1 = 0;
            if (k <= nx) {
              if (!(A[k + A.size(0) * nx] == A[nx + A.size(0) * k])) {
                p = false;
                exitg1 = 1;
              } else {
                k++;
              }
            } else {
              nx++;
              exitg1 = 2;
            }
          } while (exitg1 == 0);
          if (exitg1 == 1) {
            exitg2 = true;
          }
        }
      }
      if (p) {
        eigHermitianStandard(A, tmp_data, V_size);
        for (k = 0; k < *V_size; k++) {
          V_data[k].re = tmp_data[k];
          V_data[k].im = 0.0;
        }
      } else {
        p = (A.size(0) == A.size(1));
        if (p) {
          nx = 0;
          exitg2 = false;
          while ((!exitg2) && (nx <= A.size(1) - 1)) {
            k = 0;
            do {
              exitg1 = 0;
              if (k <= nx) {
                if (!(A[k + A.size(0) * nx] == -A[nx + A.size(0) * k])) {
                  p = false;
                  exitg1 = 1;
                } else {
                  k++;
                }
              } else {
                nx++;
                exitg1 = 2;
              }
            } while (exitg1 == 0);
            if (exitg1 == 1) {
              exitg2 = true;
            }
          }
        }
        if (p) {
          eigSkewHermitianStandard(A, V_data, V_size);
        } else {
          internal::reflapack::xzgeev(A, &nx, V_data, V_size, beta1_data, &k);
          if (*V_size == k) {
            for (k = 0; k < *V_size; k++) {
              double ai;
              double ar;
              double bi;
              double br;
              double im;
              double re;
              ar = V_data[k].re;
              ai = V_data[k].im;
              br = beta1_data[k].re;
              bi = beta1_data[k].im;
              if (bi == 0.0) {
                if (ai == 0.0) {
                  re = ar / br;
                  im = 0.0;
                } else if (ar == 0.0) {
                  re = 0.0;
                  im = ai / br;
                } else {
                  re = ar / br;
                  im = ai / br;
                }
              } else if (br == 0.0) {
                if (ar == 0.0) {
                  re = ai / bi;
                  im = 0.0;
                } else if (ai == 0.0) {
                  re = 0.0;
                  im = -(ar / bi);
                } else {
                  re = ai / bi;
                  im = -(ar / bi);
                }
              } else {
                double brm;
                brm = std::abs(br);
                im = std::abs(bi);
                if (brm > im) {
                  double s;
                  s = bi / br;
                  im = br + s * bi;
                  re = (ar + s * ai) / im;
                  im = (ai - s * ar) / im;
                } else if (im == brm) {
                  double s;
                  if (br > 0.0) {
                    s = 0.5;
                  } else {
                    s = -0.5;
                  }
                  if (bi > 0.0) {
                    im = 0.5;
                  } else {
                    im = -0.5;
                  }
                  re = (ar * s + ai * im) / brm;
                  im = (ai * s - ar * im) / brm;
                } else {
                  double s;
                  s = br / bi;
                  im = bi + s * br;
                  re = (s * ar + ai) / im;
                  im = (s * ai - ar) / im;
                }
              }
              V_data[k].re = re;
              V_data[k].im = im;
            }
          } else {
            rdivide(V_data, V_size, beta1_data, &k);
          }
        }
      }
    }
  }
}

} // namespace coder

//
// File trailer for eig.cpp
//
// [EOF]
//
