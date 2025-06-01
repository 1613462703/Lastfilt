//
// File: qrsolve.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

// Include Files
#include "qrsolve.h"
#include "rt_nonfinite.h"
#include "xgeqp3.h"
#include "coder_array.h"
#include <algorithm>
#include <cmath>
#include <cstring>

// Function Declarations
namespace coder {
namespace internal {
static int rankFromQR(const ::coder::array<double, 2U> &A);

}
} // namespace coder

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &A
// Return Type  : int
//
namespace coder {
namespace internal {
static int rankFromQR(const ::coder::array<double, 2U> &A)
{
  int maxmn;
  int minmn;
  int r;
  r = 0;
  if (A.size(0) < A.size(1)) {
    minmn = A.size(0);
    maxmn = A.size(1);
  } else {
    minmn = A.size(1);
    maxmn = A.size(0);
  }
  if (minmn > 0) {
    double tol;
    tol = 2.2204460492503131E-15 * static_cast<double>(maxmn) * std::abs(A[0]);
    while ((r < minmn) && (!(std::abs(A[r + A.size(0) * r]) <= tol))) {
      r++;
    }
  }
  return r;
}

//
// Arguments    : const ::coder::array<double, 2U> &A
//                const ::coder::array<double, 2U> &B
//                ::coder::array<double, 2U> &Y
// Return Type  : void
//
void qrsolve(const ::coder::array<double, 2U> &A,
             const ::coder::array<double, 2U> &B, ::coder::array<double, 2U> &Y)
{
  array<double, 2U> b_A;
  array<double, 2U> b_B;
  double tau_data[1002];
  int jpvt_data[1002];
  int b_nb;
  int i;
  int loop_ub;
  int m;
  int nb;
  int rankA;
  int u1;
  b_A.set_size(A.size(0), A.size(1));
  loop_ub = A.size(0) * A.size(1);
  for (i = 0; i < loop_ub; i++) {
    b_A[i] = A[i];
  }
  int jpvt_size[2];
  lapack::xgeqp3(b_A, tau_data, &loop_ub, jpvt_data, jpvt_size);
  b_B.set_size(B.size(0), B.size(1));
  loop_ub = B.size(0) * B.size(1);
  for (i = 0; i < loop_ub; i++) {
    b_B[i] = B[i];
  }
  rankA = rankFromQR(b_A);
  nb = B.size(1);
  Y.set_size(b_A.size(1), B.size(1));
  loop_ub = b_A.size(1) * B.size(1);
  for (i = 0; i < loop_ub; i++) {
    Y[i] = 0.0;
  }
  m = b_A.size(0);
  b_nb = B.size(1);
  loop_ub = b_A.size(0);
  u1 = b_A.size(1);
  if (loop_ub <= u1) {
    u1 = loop_ub;
  }
  for (loop_ub = 0; loop_ub < u1; loop_ub++) {
    if (tau_data[loop_ub] != 0.0) {
      for (int k{0}; k < b_nb; k++) {
        double wj;
        wj = b_B[loop_ub + b_B.size(0) * k];
        i = loop_ub + 2;
        for (int b_i{i}; b_i <= m; b_i++) {
          wj += b_A[(b_i + b_A.size(0) * loop_ub) - 1] *
                b_B[(b_i + b_B.size(0) * k) - 1];
        }
        wj *= tau_data[loop_ub];
        if (wj != 0.0) {
          b_B[loop_ub + b_B.size(0) * k] = b_B[loop_ub + b_B.size(0) * k] - wj;
          for (int b_i{i}; b_i <= m; b_i++) {
            b_B[(b_i + b_B.size(0) * k) - 1] =
                b_B[(b_i + b_B.size(0) * k) - 1] -
                b_A[(b_i + b_A.size(0) * loop_ub) - 1] * wj;
          }
        }
      }
    }
  }
  for (int k{0}; k < nb; k++) {
    i = static_cast<unsigned short>(rankA);
    for (int b_i{0}; b_i < i; b_i++) {
      Y[(jpvt_data[b_i] + Y.size(0) * k) - 1] = b_B[b_i + b_B.size(0) * k];
    }
    for (loop_ub = rankA; loop_ub >= 1; loop_ub--) {
      i = jpvt_data[loop_ub - 1];
      Y[(i + Y.size(0) * k) - 1] =
          Y[(i + Y.size(0) * k) - 1] /
          b_A[(loop_ub + b_A.size(0) * (loop_ub - 1)) - 1];
      i = static_cast<unsigned short>(loop_ub - 1);
      for (int b_i{0}; b_i < i; b_i++) {
        Y[(jpvt_data[b_i] + Y.size(0) * k) - 1] =
            Y[(jpvt_data[b_i] + Y.size(0) * k) - 1] -
            Y[(jpvt_data[loop_ub - 1] + Y.size(0) * k) - 1] *
                b_A[b_i + b_A.size(0) * (loop_ub - 1)];
      }
    }
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &A
//                const double B_data[]
//                int B_size
//                double Y_data[]
//                int *Y_size
// Return Type  : void
//
void qrsolve(const ::coder::array<double, 2U> &A, const double B_data[],
             int B_size, double Y_data[], int *Y_size)
{
  array<double, 2U> b_A;
  double b_B_data[1002];
  double tau_data[1002];
  int jpvt_data[1002];
  int i;
  int loop_ub;
  int m;
  int rankA;
  int u1;
  b_A.set_size(A.size(0), A.size(1));
  loop_ub = A.size(0) * A.size(1);
  for (i = 0; i < loop_ub; i++) {
    b_A[i] = A[i];
  }
  int jpvt_size[2];
  lapack::xgeqp3(b_A, tau_data, &loop_ub, jpvt_data, jpvt_size);
  if (B_size - 1 >= 0) {
    std::copy(&B_data[0], &B_data[B_size], &b_B_data[0]);
  }
  rankA = rankFromQR(b_A);
  *Y_size = b_A.size(1);
  loop_ub = b_A.size(1);
  if (loop_ub - 1 >= 0) {
    std::memset(&Y_data[0], 0,
                static_cast<unsigned int>(loop_ub) * sizeof(double));
  }
  m = b_A.size(0);
  loop_ub = b_A.size(0);
  u1 = b_A.size(1);
  if (loop_ub <= u1) {
    u1 = loop_ub;
  }
  for (loop_ub = 0; loop_ub < u1; loop_ub++) {
    if (tau_data[loop_ub] != 0.0) {
      double wj;
      wj = b_B_data[loop_ub];
      i = loop_ub + 2;
      for (int b_i{i}; b_i <= m; b_i++) {
        wj += b_A[(b_i + b_A.size(0) * loop_ub) - 1] * b_B_data[b_i - 1];
      }
      wj *= tau_data[loop_ub];
      if (wj != 0.0) {
        b_B_data[loop_ub] -= wj;
        for (int b_i{i}; b_i <= m; b_i++) {
          b_B_data[b_i - 1] -= b_A[(b_i + b_A.size(0) * loop_ub) - 1] * wj;
        }
      }
    }
  }
  i = static_cast<unsigned short>(rankA);
  for (int b_i{0}; b_i < i; b_i++) {
    Y_data[jpvt_data[b_i] - 1] = b_B_data[b_i];
  }
  for (loop_ub = rankA; loop_ub >= 1; loop_ub--) {
    i = jpvt_data[loop_ub - 1];
    Y_data[i - 1] /= b_A[(loop_ub + b_A.size(0) * (loop_ub - 1)) - 1];
    i = static_cast<unsigned short>(loop_ub - 1);
    for (int b_i{0}; b_i < i; b_i++) {
      Y_data[jpvt_data[b_i] - 1] -= Y_data[jpvt_data[loop_ub - 1] - 1] *
                                    b_A[b_i + b_A.size(0) * (loop_ub - 1)];
    }
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for qrsolve.cpp
//
// [EOF]
//
