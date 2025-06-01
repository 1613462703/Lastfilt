//
// File: lusolve.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

// Include Files
#include "lusolve.h"
#include "rt_nonfinite.h"
#include "xzgetrf.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &A
//                double B_data[]
//                const int B_size[2]
// Return Type  : void
//
namespace coder {
namespace internal {
void b_lusolve(const ::coder::array<double, 2U> &A, double B_data[],
               const int B_size[2])
{
  array<double, 2U> b_A;
  int ipiv_data[1002];
  int i;
  int i1;
  int jAcol;
  int n;
  n = A.size(1);
  b_A.set_size(A.size(0), A.size(1));
  jAcol = A.size(0) * A.size(1);
  for (i = 0; i < jAcol; i++) {
    b_A[i] = A[i];
  }
  int ipiv_size[2];
  reflapack::xzgetrf(A.size(1), A.size(1), b_A, A.size(1), ipiv_data, ipiv_size,
                     &jAcol);
  if ((A.size(1) != 0) && (B_size[1] != 0)) {
    for (int j{0}; j < n; j++) {
      jAcol = n * j;
      for (int k{0}; k < j; k++) {
        i = k + jAcol;
        if (b_A[i] != 0.0) {
          B_data[j] -= b_A[i] * B_data[k];
        }
      }
      B_data[j] *= 1.0 / b_A[j + jAcol];
    }
  }
  if ((A.size(1) != 0) && (B_size[1] != 0)) {
    for (int j{n}; j >= 1; j--) {
      jAcol = n * (j - 1) - 1;
      i = j + 1;
      for (int k{i}; k <= n; k++) {
        i1 = k + jAcol;
        if (b_A[i1] != 0.0) {
          B_data[j - 1] -= b_A[i1] * B_data[k - 1];
        }
      }
    }
  }
  i = A.size(1) - 1;
  for (int j{i}; j >= 1; j--) {
    i1 = ipiv_data[j - 1];
    if (i1 != j) {
      double temp;
      temp = B_data[j - 1];
      B_data[j - 1] = B_data[i1 - 1];
      B_data[i1 - 1] = temp;
    }
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &A
//                ::coder::array<double, 2U> &B
// Return Type  : void
//
void lusolve(const ::coder::array<double, 2U> &A, ::coder::array<double, 2U> &B)
{
  array<double, 2U> b_A;
  int ipiv_data[1002];
  int i;
  int i1;
  int i2;
  int jBcol;
  int kAcol;
  int n;
  int nrhs;
  jBcol = A.size(0);
  n = A.size(1);
  if (jBcol <= n) {
    n = jBcol;
  }
  jBcol = B.size(0);
  if (jBcol <= n) {
    n = jBcol;
  }
  nrhs = B.size(1) - 1;
  b_A.set_size(A.size(0), A.size(1));
  jBcol = A.size(0) * A.size(1);
  for (i = 0; i < jBcol; i++) {
    b_A[i] = A[i];
  }
  int ipiv_size[2];
  reflapack::xzgetrf(n, n, b_A, A.size(0), ipiv_data, ipiv_size, &jBcol);
  for (int b_i{0}; b_i <= n - 2; b_i++) {
    i = ipiv_data[b_i];
    if (i != b_i + 1) {
      for (int j{0}; j <= nrhs; j++) {
        double temp;
        temp = B[b_i + B.size(0) * j];
        B[b_i + B.size(0) * j] = B[(i + B.size(0) * j) - 1];
        B[(i + B.size(0) * j) - 1] = temp;
      }
    }
  }
  if ((B.size(1) != 0) && ((B.size(0) != 0) && (B.size(1) != 0))) {
    for (int j{0}; j <= nrhs; j++) {
      jBcol = B.size(0) * j;
      for (int k{0}; k < n; k++) {
        kAcol = b_A.size(0) * k;
        i = k + jBcol;
        if (B[i] != 0.0) {
          i1 = k + 2;
          for (int b_i{i1}; b_i <= n; b_i++) {
            i2 = (b_i + jBcol) - 1;
            B[i2] = B[i2] - B[i] * b_A[(b_i + kAcol) - 1];
          }
        }
      }
    }
  }
  if ((B.size(1) != 0) && ((B.size(0) != 0) && (B.size(1) != 0))) {
    i = B.size(1);
    for (int j{0}; j < i; j++) {
      jBcol = B.size(0) * j - 1;
      for (int k{n}; k >= 1; k--) {
        kAcol = b_A.size(0) * (k - 1) - 1;
        i1 = k + jBcol;
        if (B[i1] != 0.0) {
          B[i1] = B[i1] / b_A[k + kAcol];
          for (int b_i{0}; b_i <= k - 2; b_i++) {
            i2 = (b_i + jBcol) + 1;
            B[i2] = B[i2] - B[i1] * b_A[(b_i + kAcol) + 1];
          }
        }
      }
    }
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &A
//                double B_data[]
//                const int *B_size
// Return Type  : void
//
void lusolve(const ::coder::array<double, 2U> &A, double B_data[],
             const int *B_size)
{
  array<double, 2U> b_A;
  double temp;
  int ipiv_data[1002];
  int LDA;
  int i;
  int kAcol;
  int n;
  LDA = A.size(0);
  n = A.size(1);
  if (LDA <= n) {
    n = LDA;
  }
  LDA = *B_size;
  if (LDA <= n) {
    n = LDA;
  }
  b_A.set_size(A.size(0), A.size(1));
  LDA = A.size(0) * A.size(1);
  for (i = 0; i < LDA; i++) {
    b_A[i] = A[i];
  }
  int ipiv_size[2];
  reflapack::xzgetrf(n, n, b_A, A.size(0), ipiv_data, ipiv_size, &LDA);
  LDA = b_A.size(0);
  for (int b_i{0}; b_i <= n - 2; b_i++) {
    i = ipiv_data[b_i];
    if (i != b_i + 1) {
      temp = B_data[b_i];
      B_data[b_i] = B_data[i - 1];
      B_data[i - 1] = temp;
    }
  }
  for (int k{0}; k < n; k++) {
    kAcol = LDA * k;
    if (B_data[k] != 0.0) {
      i = k + 2;
      for (int b_i{i}; b_i <= n; b_i++) {
        B_data[b_i - 1] -= B_data[k] * b_A[(b_i + kAcol) - 1];
      }
    }
  }
  for (int k{n}; k >= 1; k--) {
    kAcol = LDA * (k - 1);
    temp = B_data[k - 1];
    if (temp != 0.0) {
      temp /= b_A[(k + kAcol) - 1];
      B_data[k - 1] = temp;
      for (int b_i{0}; b_i <= k - 2; b_i++) {
        B_data[b_i] -= B_data[k - 1] * b_A[b_i + kAcol];
      }
    }
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for lusolve.cpp
//
// [EOF]
//
