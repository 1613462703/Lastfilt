//
// File: xgehrd.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

// Include Files
#include "xgehrd.h"
#include "rt_nonfinite.h"
#include "xgerc.h"
#include "xzlarfg.h"
#include "coder_array.h"
#include <cstring>

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &a
// Return Type  : void
//
namespace coder {
namespace internal {
namespace lapack {
void xgehrd(::coder::array<double, 2U> &a)
{
  double work_data[1002];
  double tau_data[1001];
  double alpha1;
  int b_i;
  int i;
  int n;
  short unnamed_idx_0;
  n = a.size(0);
  unnamed_idx_0 = static_cast<short>(a.size(0));
  i = unnamed_idx_0;
  if (i - 1 >= 0) {
    std::memset(&work_data[0], 0,
                static_cast<unsigned int>(i) * sizeof(double));
  }
  b_i = a.size(0);
  for (int c_i{0}; c_i <= b_i - 2; c_i++) {
    double temp;
    int exitg1;
    int i1;
    int i2;
    int ia;
    int ic0;
    int in;
    int iv0_tmp;
    int lastc;
    int lastv;
    int n_tmp_tmp;
    boolean_T exitg2;
    in = (c_i + 1) * n;
    alpha1 = a[(c_i + a.size(0) * c_i) + 1];
    i = c_i + 3;
    if (i > n) {
      i = n;
    }
    temp = reflapack::xzlarfg((n - c_i) - 1, &alpha1, a, i + c_i * n);
    tau_data[c_i] = temp;
    a[(c_i + a.size(0) * c_i) + 1] = 1.0;
    n_tmp_tmp = n - c_i;
    iv0_tmp = (c_i + c_i * n) + 2;
    ic0 = in + 1;
    if (temp != 0.0) {
      lastv = n_tmp_tmp - 2;
      i = (iv0_tmp + n_tmp_tmp) - 4;
      while ((lastv + 1 > 0) && (a[i + 1] == 0.0)) {
        lastv--;
        i--;
      }
      lastc = n;
      exitg2 = false;
      while ((!exitg2) && (lastc > 0)) {
        i = in + lastc;
        ia = i;
        do {
          exitg1 = 0;
          if ((n > 0) && (ia <= i + lastv * n)) {
            if (a[ia - 1] != 0.0) {
              exitg1 = 1;
            } else {
              ia += n;
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
      lastv = -1;
      lastc = 0;
    }
    if (lastv + 1 > 0) {
      int work_tmp;
      if (lastc != 0) {
        std::memset(&work_data[0], 0,
                    static_cast<unsigned int>(lastc) * sizeof(double));
        i = iv0_tmp - 1;
        i1 = (in + n * lastv) + 1;
        for (int iac{ic0}; n < 0 ? iac >= i1 : iac <= i1; iac += n) {
          i2 = (iac + lastc) - 1;
          for (ia = iac; ia <= i2; ia++) {
            work_tmp = ia - iac;
            work_data[work_tmp] += a[ia - 1] * a[i];
          }
          i++;
        }
      }
      if (!(-tau_data[c_i] == 0.0)) {
        i = in;
        for (work_tmp = 0; work_tmp <= lastv; work_tmp++) {
          i1 = (iv0_tmp + work_tmp) - 1;
          if (a[i1] != 0.0) {
            temp = a[i1] * -tau_data[c_i];
            i1 = i + 1;
            i2 = lastc + i;
            for (int iac{i1}; iac <= i2; iac++) {
              a[iac - 1] = a[iac - 1] + work_data[(iac - i) - 1] * temp;
            }
          }
          i += n;
        }
      }
    }
    ic0 = (c_i + in) + 2;
    if (tau_data[c_i] != 0.0) {
      lastv = n_tmp_tmp - 1;
      i = (iv0_tmp + n_tmp_tmp) - 3;
      while ((lastv > 0) && (a[i] == 0.0)) {
        lastv--;
        i--;
      }
      lastc = n_tmp_tmp - 1;
      exitg2 = false;
      while ((!exitg2) && (lastc > 0)) {
        i = ic0 + (lastc - 1) * n;
        ia = i;
        do {
          exitg1 = 0;
          if (ia <= (i + lastv) - 1) {
            if (a[ia - 1] != 0.0) {
              exitg1 = 1;
            } else {
              ia++;
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
        i = 0;
        i1 = ic0 + n * (lastc - 1);
        for (int iac{ic0}; n < 0 ? iac >= i1 : iac <= i1; iac += n) {
          temp = 0.0;
          i2 = (iac + lastv) - 1;
          for (ia = iac; ia <= i2; ia++) {
            temp += a[ia - 1] * a[((iv0_tmp + ia) - iac) - 1];
          }
          work_data[i] += temp;
          i++;
        }
      }
      blas::xgerc(lastv, lastc, -tau_data[c_i], iv0_tmp, work_data, a, ic0, n);
    }
    a[(c_i + a.size(0) * c_i) + 1] = alpha1;
  }
}

} // namespace lapack
} // namespace internal
} // namespace coder

//
// File trailer for xgehrd.cpp
//
// [EOF]
//
