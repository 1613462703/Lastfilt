//
// File: xzgeqp3.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

// Include Files
#include "xzgeqp3.h"
#include "rt_nonfinite.h"
#include "xgerc.h"
#include "xnrm2.h"
#include "xzlarfg.h"
#include "coder_array.h"
#include <cmath>
#include <cstring>

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &A
//                int m
//                int n
//                double tau_data[]
//                int jpvt_data[]
// Return Type  : void
//
namespace coder {
namespace internal {
namespace reflapack {
void qrpf(::coder::array<double, 2U> &A, int m, int n, double tau_data[],
          int jpvt_data[])
{
  double vn1_data[1002];
  double vn2_data[1002];
  double work_data[1002];
  double d;
  double s;
  int i;
  int ix;
  int j;
  int ma;
  ma = A.size(0);
  ix = A.size(1);
  if (ix - 1 >= 0) {
    std::memset(&work_data[0], 0,
                static_cast<unsigned int>(ix) * sizeof(double));
  }
  ix = A.size(1);
  if (ix - 1 >= 0) {
    std::memset(&vn1_data[0], 0,
                static_cast<unsigned int>(ix) * sizeof(double));
  }
  ix = A.size(1);
  if (ix - 1 >= 0) {
    std::memset(&vn2_data[0], 0,
                static_cast<unsigned int>(ix) * sizeof(double));
  }
  i = static_cast<unsigned short>(n);
  for (j = 0; j < i; j++) {
    d = blas::xnrm2(m, A, j * ma + 1);
    vn1_data[j] = d;
    vn2_data[j] = d;
  }
  if (m <= n) {
    ix = m;
  } else {
    ix = n;
  }
  i = static_cast<unsigned short>(ix);
  for (int b_i{0}; b_i < i; b_i++) {
    double smax;
    int i1;
    int i2;
    int ii;
    int ip1;
    int lastc;
    int lastv;
    int mmi;
    int nmi;
    int pvt;
    ip1 = b_i + 2;
    lastc = b_i * ma;
    ii = lastc + b_i;
    nmi = n - b_i;
    mmi = (m - b_i) - 1;
    if (nmi < 1) {
      ix = -1;
    } else {
      ix = 0;
      if (nmi > 1) {
        smax = std::abs(vn1_data[b_i]);
        for (lastv = 2; lastv <= nmi; lastv++) {
          s = std::abs(vn1_data[(b_i + lastv) - 1]);
          if (s > smax) {
            ix = lastv - 1;
            smax = s;
          }
        }
      }
    }
    pvt = b_i + ix;
    if (pvt + 1 != b_i + 1) {
      ix = pvt * ma;
      i1 = static_cast<unsigned short>(m);
      for (lastv = 0; lastv < i1; lastv++) {
        j = ix + lastv;
        smax = A[j];
        i2 = lastc + lastv;
        A[j] = A[i2];
        A[i2] = smax;
      }
      ix = jpvt_data[pvt];
      jpvt_data[pvt] = jpvt_data[b_i];
      jpvt_data[b_i] = ix;
      vn1_data[pvt] = vn1_data[b_i];
      vn2_data[pvt] = vn2_data[b_i];
    }
    if (b_i + 1 < m) {
      s = A[ii];
      d = xzlarfg(mmi + 1, &s, A, ii + 2);
      tau_data[b_i] = d;
      A[ii] = s;
    } else {
      d = 0.0;
      tau_data[b_i] = 0.0;
    }
    if (b_i + 1 < n) {
      s = A[ii];
      A[ii] = 1.0;
      pvt = (ii + ma) + 1;
      if (d != 0.0) {
        boolean_T exitg2;
        lastv = mmi + 1;
        ix = ii + mmi;
        while ((lastv > 0) && (A[ix] == 0.0)) {
          lastv--;
          ix--;
        }
        lastc = nmi - 1;
        exitg2 = false;
        while ((!exitg2) && (lastc > 0)) {
          int exitg1;
          ix = pvt + (lastc - 1) * ma;
          nmi = ix;
          do {
            exitg1 = 0;
            if (nmi <= (ix + lastv) - 1) {
              if (A[nmi - 1] != 0.0) {
                exitg1 = 1;
              } else {
                nmi++;
              }
            } else {
              lastc--;
              exitg1 = 2;
            }
          } while (exitg1 == 0);
          if (exitg1 == 1) {
            exitg2 = true;
          }
        }
      } else {
        lastv = 0;
        lastc = 0;
      }
      if (lastv > 0) {
        if (lastc != 0) {
          if (lastc - 1 >= 0) {
            std::memset(&work_data[0], 0,
                        static_cast<unsigned int>(lastc) * sizeof(double));
          }
          j = 0;
          i1 = pvt + ma * (lastc - 1);
          for (ix = pvt; ma < 0 ? ix >= i1 : ix <= i1; ix += ma) {
            smax = 0.0;
            i2 = (ix + lastv) - 1;
            for (nmi = ix; nmi <= i2; nmi++) {
              smax += A[nmi - 1] * A[(ii + nmi) - ix];
            }
            work_data[j] += smax;
            j++;
          }
        }
        blas::xgerc(lastv, lastc, -tau_data[b_i], ii + 1, work_data, A, pvt,
                    ma);
      }
      A[ii] = s;
    }
    for (j = ip1; j <= n; j++) {
      ix = b_i + (j - 1) * ma;
      d = vn1_data[j - 1];
      if (d != 0.0) {
        smax = std::abs(A[ix]) / d;
        smax = 1.0 - smax * smax;
        if (smax < 0.0) {
          smax = 0.0;
        }
        s = d / vn2_data[j - 1];
        s = smax * (s * s);
        if (s <= 1.4901161193847656E-8) {
          if (b_i + 1 < m) {
            d = blas::xnrm2(mmi, A, ix + 2);
            vn1_data[j - 1] = d;
            vn2_data[j - 1] = d;
          } else {
            vn1_data[j - 1] = 0.0;
            vn2_data[j - 1] = 0.0;
          }
        } else {
          vn1_data[j - 1] = d * std::sqrt(smax);
        }
      }
    }
  }
}

} // namespace reflapack
} // namespace internal
} // namespace coder

//
// File trailer for xzgeqp3.cpp
//
// [EOF]
//
