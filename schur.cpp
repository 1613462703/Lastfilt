//
// File: schur.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

// Include Files
#include "schur.h"
#include "rt_nonfinite.h"
#include "xdhseqr.h"
#include "xgehrd.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &A
//                ::coder::array<double, 2U> &V
// Return Type  : void
//
namespace coder {
void schur(::coder::array<double, 2U> &A, ::coder::array<double, 2U> &V)
{
  int istart;
  int nx;
  boolean_T p;
  nx = A.size(0) * A.size(1);
  p = true;
  for (istart = 0; istart < nx; istart++) {
    if ((!p) || (std::isinf(A[istart]) || std::isnan(A[istart]))) {
      p = false;
    }
  }
  if (!p) {
    int i;
    V.set_size(static_cast<int>(static_cast<short>(A.size(0))),
               static_cast<int>(static_cast<short>(A.size(1))));
    nx = static_cast<short>(A.size(0)) * static_cast<short>(A.size(1));
    for (i = 0; i < nx; i++) {
      V[i] = rtNaN;
    }
    nx = static_cast<short>(A.size(0));
    if ((static_cast<short>(A.size(0)) != 0) &&
        (static_cast<short>(A.size(1)) != 0) &&
        (static_cast<short>(A.size(0)) > 1)) {
      istart = 2;
      if (static_cast<short>(A.size(0)) - 2 <
          static_cast<short>(A.size(1)) - 1) {
        i = static_cast<short>(A.size(0)) - 1;
      } else {
        i = static_cast<short>(A.size(1));
      }
      for (int j{0}; j < i; j++) {
        for (int b_i{istart}; b_i <= nx; b_i++) {
          V[(b_i + V.size(0) * j) - 1] = 0.0;
        }
        istart++;
      }
    }
  } else {
    int i;
    internal::lapack::xgehrd(A);
    V.set_size(A.size(0), A.size(1));
    nx = A.size(0) * A.size(1);
    for (i = 0; i < nx; i++) {
      V[i] = A[i];
    }
    internal::reflapack::eml_dlahqr(V);
    nx = V.size(0);
    if ((V.size(0) != 0) && (V.size(1) != 0) && (V.size(0) > 3)) {
      istart = 4;
      if (V.size(0) - 4 < V.size(1) - 1) {
        i = V.size(0) - 3;
      } else {
        i = V.size(1);
      }
      for (int j{0}; j < i; j++) {
        for (int b_i{istart}; b_i <= nx; b_i++) {
          V[(b_i + V.size(0) * j) - 1] = 0.0;
        }
        istart++;
      }
    }
  }
}

} // namespace coder

//
// File trailer for schur.cpp
//
// [EOF]
//
