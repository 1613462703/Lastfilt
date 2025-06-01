//
// File: xgeqp3.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

// Include Files
#include "xgeqp3.h"
#include "rt_nonfinite.h"
#include "xzgeqp3.h"
#include "coder_array.h"
#include <cstring>

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &A
//                double tau_data[]
//                int *tau_size
//                int jpvt_data[]
//                int jpvt_size[2]
// Return Type  : void
//
namespace coder {
namespace internal {
namespace lapack {
void xgeqp3(::coder::array<double, 2U> &A, double tau_data[], int *tau_size,
            int jpvt_data[], int jpvt_size[2])
{
  int u0;
  int u1;
  boolean_T guard1{false};
  u0 = A.size(0);
  *tau_size = A.size(1);
  if (u0 <= *tau_size) {
    *tau_size = u0;
  }
  if (*tau_size - 1 >= 0) {
    std::memset(&tau_data[0], 0,
                static_cast<unsigned int>(*tau_size) * sizeof(double));
  }
  guard1 = false;
  if ((A.size(0) == 0) || (A.size(1) == 0)) {
    guard1 = true;
  } else {
    u0 = A.size(0);
    u1 = A.size(1);
    if (u0 <= u1) {
      u1 = u0;
    }
    if (u1 < 1) {
      guard1 = true;
    } else {
      jpvt_size[0] = 1;
      jpvt_size[1] = A.size(1);
      u0 = A.size(1);
      if (u0 - 1 >= 0) {
        std::memset(&jpvt_data[0], 0,
                    static_cast<unsigned int>(u0) * sizeof(int));
      }
      u0 = A.size(1);
      for (u1 = 0; u1 < u0; u1++) {
        jpvt_data[u1] = u1 + 1;
      }
      reflapack::qrpf(A, A.size(0), A.size(1), tau_data, jpvt_data);
    }
  }
  if (guard1) {
    jpvt_size[0] = 1;
    jpvt_size[1] = A.size(1);
    u0 = A.size(1);
    if (u0 - 1 >= 0) {
      std::memset(&jpvt_data[0], 0,
                  static_cast<unsigned int>(u0) * sizeof(int));
    }
    u0 = A.size(1);
    for (u1 = 0; u1 < u0; u1++) {
      jpvt_data[u1] = u1 + 1;
    }
  }
}

} // namespace lapack
} // namespace internal
} // namespace coder

//
// File trailer for xgeqp3.cpp
//
// [EOF]
//
