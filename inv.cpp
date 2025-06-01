//
// File: inv.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

// Include Files
#include "inv.h"
#include "rt_nonfinite.h"
#include "xgetrf.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &x
//                ::coder::array<double, 2U> &y
// Return Type  : void
//
namespace coder {
void inv(const ::coder::array<double, 2U> &x, ::coder::array<double, 2U> &y)
{
  array<double, 2U> B;
  array<double, 2U> b_x;
  int ipiv_data[501];
  if ((x.size(0) == 0) || (x.size(1) == 0)) {
    int b_n;
    y.set_size(x.size(0), x.size(1));
    b_n = x.size(0) * x.size(1);
    for (int i{0}; i < b_n; i++) {
      y[i] = x[i];
    }
  } else {
    int ipiv_size[2];
    int b_n;
    int i;
    int i1;
    int m;
    int n;
    int yk;
    short y_data[1002];
    n = x.size(0);
    y.set_size(x.size(0), x.size(1));
    b_n = x.size(0) * x.size(1);
    for (i = 0; i < b_n; i++) {
      y[i] = 0.0;
    }
    b_x.set_size(x.size(0), x.size(1));
    b_n = x.size(0) * x.size(1);
    for (i = 0; i < b_n; i++) {
      b_x[i] = x[i];
    }
    internal::lapack::xgetrf(x.size(0), x.size(0), b_x, x.size(0), ipiv_data,
                             ipiv_size);
    b_n = x.size(0);
    y_data[0] = 1;
    yk = 1;
    for (int k{2}; k <= b_n; k++) {
      yk++;
      y_data[k - 1] = static_cast<short>(yk);
    }
    i = ipiv_size[1];
    for (int k{0}; k < i; k++) {
      i1 = ipiv_data[k];
      if (i1 > k + 1) {
        b_n = y_data[i1 - 1];
        y_data[i1 - 1] = y_data[k];
        y_data[k] = static_cast<short>(b_n);
      }
    }
    for (int k{0}; k < n; k++) {
      short i2;
      i2 = y_data[k];
      y[k + y.size(0) * (i2 - 1)] = 1.0;
      for (int j{k + 1}; j <= n; j++) {
        if (y[(j + y.size(0) * (i2 - 1)) - 1] != 0.0) {
          i = j + 1;
          for (int b_i{i}; b_i <= n; b_i++) {
            y[(b_i + y.size(0) * (i2 - 1)) - 1] =
                y[(b_i + y.size(0) * (i2 - 1)) - 1] -
                y[(j + y.size(0) * (i2 - 1)) - 1] *
                    b_x[(b_i + b_x.size(0) * (j - 1)) - 1];
          }
        }
      }
    }
    m = x.size(0);
    B.set_size(y.size(0), y.size(1));
    b_n = y.size(0) * y.size(1);
    for (i = 0; i < b_n; i++) {
      B[i] = y[i];
    }
    i = x.size(0);
    for (int j{0}; j < i; j++) {
      b_n = x.size(0) * j - 1;
      for (int k{m}; k >= 1; k--) {
        yk = x.size(0) * (k - 1) - 1;
        i1 = k + b_n;
        if (B[i1] != 0.0) {
          B[i1] = B[i1] / b_x[k + yk];
          for (int b_i{0}; b_i <= k - 2; b_i++) {
            n = (b_i + b_n) + 1;
            B[n] = B[n] - B[i1] * b_x[(b_i + yk) + 1];
          }
        }
      }
    }
    y.set_size(B.size(0), B.size(1));
    b_n = B.size(0) * B.size(1);
    for (i = 0; i < b_n; i++) {
      y[i] = B[i];
    }
  }
}

} // namespace coder

//
// File trailer for inv.cpp
//
// [EOF]
//
