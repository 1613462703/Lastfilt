//
// File: xzgetrf.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

// Include Files
#include "xzgetrf.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : int m
//                int n
//                ::coder::array<double, 2U> &A
//                int lda
//                int ipiv_data[]
//                int ipiv_size[2]
//                int *info
// Return Type  : void
//
namespace coder {
namespace internal {
namespace reflapack {
void xzgetrf(int m, int n, ::coder::array<double, 2U> &A, int lda,
             int ipiv_data[], int ipiv_size[2], int *info)
{
  int b_n;
  int yk;
  if (m <= n) {
    yk = m;
  } else {
    yk = n;
  }
  if (yk < 1) {
    b_n = 0;
  } else {
    b_n = static_cast<unsigned short>(yk - 1) + 1;
  }
  ipiv_size[0] = 1;
  ipiv_size[1] = b_n;
  if (b_n > 0) {
    ipiv_data[0] = 1;
    yk = 1;
    for (int k{2}; k <= b_n; k++) {
      yk++;
      ipiv_data[k - 1] = yk;
    }
  }
  *info = 0;
  if ((m >= 1) && (n >= 1)) {
    int i;
    yk = m - 1;
    if (yk > n) {
      yk = n;
    }
    i = static_cast<unsigned short>(yk);
    for (int j{0}; j < i; j++) {
      double smax;
      int b_tmp;
      int i1;
      int i2;
      int ipiv_tmp;
      int jA;
      int jp1j;
      int mmj;
      mmj = m - j;
      b_tmp = j * (lda + 1);
      jp1j = b_tmp + 2;
      if (mmj < 1) {
        yk = -1;
      } else {
        yk = 0;
        if (mmj > 1) {
          smax = std::abs(A[b_tmp]);
          for (int k{2}; k <= mmj; k++) {
            double s;
            s = std::abs(A[(b_tmp + k) - 1]);
            if (s > smax) {
              yk = k - 1;
              smax = s;
            }
          }
        }
      }
      if (A[b_tmp + yk] != 0.0) {
        if (yk != 0) {
          ipiv_tmp = j + yk;
          ipiv_data[j] = ipiv_tmp + 1;
          i1 = static_cast<unsigned short>(n);
          for (int k{0}; k < i1; k++) {
            yk = k * lda;
            jA = j + yk;
            smax = A[jA];
            i2 = ipiv_tmp + yk;
            A[jA] = A[i2];
            A[i2] = smax;
          }
        }
        i1 = b_tmp + mmj;
        for (yk = jp1j; yk <= i1; yk++) {
          A[yk - 1] = A[yk - 1] / A[b_tmp];
        }
      } else {
        *info = j + 1;
      }
      b_n = n - j;
      ipiv_tmp = b_tmp + lda;
      jA = ipiv_tmp;
      for (jp1j = 0; jp1j <= b_n - 2; jp1j++) {
        yk = ipiv_tmp + jp1j * lda;
        smax = A[yk];
        if (A[yk] != 0.0) {
          i1 = jA + 2;
          i2 = mmj + jA;
          for (yk = i1; yk <= i2; yk++) {
            A[yk - 1] = A[yk - 1] + A[((b_tmp + yk) - jA) - 1] * -smax;
          }
        }
        jA += lda;
      }
    }
    if ((*info == 0) && (m <= n) &&
        (!(A[(m + A.size(0) * (m - 1)) - 1] != 0.0))) {
      *info = m;
    }
  }
}

} // namespace reflapack
} // namespace internal
} // namespace coder

//
// File trailer for xzgetrf.cpp
//
// [EOF]
//
