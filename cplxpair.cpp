//
// File: cplxpair.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

// Include Files
#include "cplxpair.h"
#include "lastfilt_rtwutil.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>

// Function Definitions
//
// Arguments    : creal_T x_data[]
//                const int *x_size
//                double tol
// Return Type  : boolean_T
//
namespace coder {
namespace internal {
boolean_T cplxpairv(creal_T x_data[], const int *x_size, double tol)
{
  double absx_data[501];
  double zi_data[501];
  double zr_data[501];
  double zr0;
  int b_iwork_data[501];
  int idx_data[501];
  int iwork_data[501];
  int b_i;
  int i;
  int i2;
  int j;
  int k;
  int kEnd;
  int n;
  int nc;
  int nr;
  int p;
  int q;
  int qEnd;
  boolean_T exitg1;
  boolean_T pairable;
  n = *x_size;
  nr = *x_size;
  for (i = 0; i < *x_size; i++) {
    zr_data[i] = x_data[i].re;
  }
  if (nr - 1 >= 0) {
    std::memset(&idx_data[0], 0, static_cast<unsigned int>(nr) * sizeof(int));
  }
  i = nr - 1;
  for (k = 1; k <= i; k += 2) {
    zr0 = zr_data[k];
    if ((zr_data[k - 1] <= zr0) || std::isnan(zr0)) {
      idx_data[k - 1] = k;
      idx_data[k] = k + 1;
    } else {
      idx_data[k - 1] = k + 1;
      idx_data[k] = k;
    }
  }
  if ((nr & 1) != 0) {
    idx_data[nr - 1] = nr;
  }
  b_i = 2;
  while (b_i < nr) {
    i2 = b_i << 1;
    j = 1;
    for (int pEnd{b_i + 1}; pEnd < nr + 1; pEnd = qEnd + b_i) {
      p = j;
      q = pEnd - 1;
      qEnd = j + i2;
      if (qEnd > nr + 1) {
        qEnd = nr + 1;
      }
      k = 0;
      kEnd = qEnd - j;
      while (k + 1 <= kEnd) {
        zr0 = zr_data[idx_data[q] - 1];
        i = idx_data[p - 1];
        if ((zr_data[i - 1] <= zr0) || std::isnan(zr0)) {
          iwork_data[k] = i;
          p++;
          if (p == pEnd) {
            while (q + 1 < qEnd) {
              k++;
              iwork_data[k] = idx_data[q];
              q++;
            }
          }
        } else {
          iwork_data[k] = idx_data[q];
          q++;
          if (q + 1 == qEnd) {
            while (p < pEnd) {
              k++;
              iwork_data[k] = idx_data[p - 1];
              p++;
            }
          }
        }
        k++;
      }
      for (k = 0; k < kEnd; k++) {
        idx_data[(j + k) - 1] = iwork_data[k];
      }
      j = qEnd;
    }
    b_i = i2;
  }
  nr = 0;
  nc = -1;
  for (k = 0; k < n; k++) {
    double absxk;
    double absxk_tmp;
    i = idx_data[k];
    zr0 = x_data[i - 1].re;
    absxk_tmp = x_data[i - 1].im;
    absxk = rt_hypotd_snf(zr0, absxk_tmp);
    if (std::abs(x_data[i - 1].im) <= tol * absxk) {
      nr++;
      b_i = n - nr;
      zr_data[b_i] = zr0;
      zi_data[b_i] = 0.0;
      absx_data[k] = absxk;
    } else {
      nc++;
      zr_data[nc] = zr0;
      zi_data[nc] = absxk_tmp;
      absx_data[nc] = absxk;
    }
  }
  for (k = 0; k < nr; k++) {
    i = (nc + k) + 1;
    x_data[i].re = zr_data[(n - k) - 1];
    x_data[i].im = 0.0;
  }
  for (k = 0; k <= nc; k++) {
    x_data[k].re = zr_data[k];
    x_data[k].im = zi_data[k];
  }
  pairable = (((nc + 1) & 1) != 1);
  if (pairable) {
    k = 1;
    exitg1 = false;
    while ((!exitg1) && (k <= nc + 1)) {
      if (zr_data[k] - zr_data[k - 1] > tol * absx_data[k - 1]) {
        pairable = false;
        exitg1 = true;
      } else {
        k += 2;
      }
    }
  }
  if (pairable) {
    k = 1;
    exitg1 = false;
    while ((!exitg1) && (k < nc + 1)) {
      int ng;
      int offset;
      zr0 = zr_data[k - 1];
      n = k;
      offset = k - 2;
      while ((k < nc + 1) && (zr_data[k] - zr0 <= tol * absx_data[k - 1])) {
        k++;
      }
      ng = (k - n) + 1;
      nr = ng & 1;
      pairable = (nr == 0);
      if (!pairable) {
        exitg1 = true;
      } else {
        int b_k;
        boolean_T exitg2;
        i = ng - 1;
        for (b_k = 1; b_k <= i; b_k += 2) {
          b_i = offset + b_k;
          zr0 = zi_data[b_i + 1];
          if ((zi_data[b_i] <= zr0) || std::isnan(zr0)) {
            idx_data[b_i] = b_k;
            idx_data[b_i + 1] = b_k + 1;
          } else {
            idx_data[b_i] = b_k + 1;
            idx_data[b_i + 1] = b_k;
          }
        }
        if (nr != 0) {
          idx_data[offset + ng] = ng;
        }
        b_i = 2;
        while (b_i < ng) {
          i2 = b_i << 1;
          j = 1;
          for (int pEnd{b_i + 1}; pEnd < ng + 1; pEnd = qEnd + b_i) {
            p = j;
            q = pEnd;
            qEnd = j + i2;
            if (qEnd > ng + 1) {
              qEnd = ng + 1;
            }
            b_k = 0;
            kEnd = qEnd - j;
            while (b_k + 1 <= kEnd) {
              nr = idx_data[offset + q];
              zr0 = zi_data[offset + nr];
              i = idx_data[offset + p];
              if ((zi_data[offset + i] <= zr0) || std::isnan(zr0)) {
                b_iwork_data[b_k] = i;
                p++;
                if (p == pEnd) {
                  while (q < qEnd) {
                    b_k++;
                    b_iwork_data[b_k] = idx_data[offset + q];
                    q++;
                  }
                }
              } else {
                b_iwork_data[b_k] = nr;
                q++;
                if (q == qEnd) {
                  while (p < pEnd) {
                    b_k++;
                    b_iwork_data[b_k] = idx_data[offset + p];
                    p++;
                  }
                }
              }
              b_k++;
            }
            for (b_k = 0; b_k < kEnd; b_k++) {
              idx_data[(offset + j) + b_k] = b_iwork_data[b_k];
            }
            j = qEnd;
          }
          b_i = i2;
        }
        j = n;
        exitg2 = false;
        while ((!exitg2) && (j <= k)) {
          nr = offset + idx_data[j - 1];
          if (std::abs(zi_data[nr] +
                       zi_data[offset + idx_data[((k - j) + n) - 1]]) >
              tol * absx_data[nr]) {
            pairable = false;
            exitg2 = true;
          } else {
            j++;
          }
        }
        if (!pairable) {
          exitg1 = true;
        } else {
          b_i = ng >> 1;
          for (j = 0; j < b_i; j++) {
            nr = offset + idx_data[(k - j) - 1];
            i = offset + ((j + 1) << 1);
            x_data[i - 1].re = zr_data[nr];
            x_data[i - 1].im = -zi_data[nr];
            x_data[i].re = zr_data[nr];
            x_data[i].im = zi_data[nr];
          }
          k++;
        }
      }
    }
  }
  return pairable;
}

} // namespace internal
} // namespace coder

//
// File trailer for cplxpair.cpp
//
// [EOF]
//
