//
// File: lp2hp.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

// Include Files
#include "lp2hp.h"
#include "inv.h"
#include "lusolve.h"
#include "qrsolve.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <algorithm>
#include <cstring>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &a
//                const double b_data[]
//                int b_size
//                const double c_data[]
//                const int c_size[2]
//                double d
//                double wo
//                ::coder::array<double, 2U> &at
//                double bt_data[]
//                int *bt_size
//                double ct_data[]
//                int ct_size[2]
//                double *dt
// Return Type  : void
//
namespace coder {
void lp2hp(const ::coder::array<double, 2U> &a, const double b_data[],
           int b_size, const double c_data[], const int c_size[2], double d,
           double wo, ::coder::array<double, 2U> &at, double bt_data[],
           int *bt_size, double ct_data[], int ct_size[2], double *dt)
{
  array<double, 2U> b_a;
  double Y_data[1002];
  double b_c_data[1002];
  int b_Y_size[2];
  int Y_size;
  int loop_ub;
  inv(a, at);
  loop_ub = at.size(0) * at.size(1);
  for (int i{0}; i < loop_ub; i++) {
    at[i] = wo * at[i];
  }
  if ((a.size(0) == 0) || (a.size(1) == 0) || (b_size == 0)) {
    Y_size = a.size(1);
    loop_ub = a.size(1);
    if (loop_ub - 1 >= 0) {
      std::memset(&Y_data[0], 0,
                  static_cast<unsigned int>(loop_ub) * sizeof(double));
    }
  } else if (a.size(0) == a.size(1)) {
    Y_size = b_size;
    std::copy(&b_data[0], &b_data[b_size], &Y_data[0]);
    internal::lusolve(a, Y_data, &Y_size);
  } else {
    internal::qrsolve(a, b_data, b_size, Y_data, &Y_size);
  }
  *bt_size = Y_size;
  for (int i{0}; i < Y_size; i++) {
    bt_data[i] = -wo * Y_data[i];
  }
  if ((c_size[1] == 0) || ((a.size(0) == 0) || (a.size(1) == 0))) {
    b_Y_size[1] = a.size(0);
    loop_ub = a.size(0);
    if (loop_ub - 1 >= 0) {
      std::memset(&b_c_data[0], 0,
                  static_cast<unsigned int>(loop_ub) * sizeof(double));
    }
  } else if (a.size(0) == a.size(1)) {
    b_Y_size[0] = 1;
    b_Y_size[1] = c_size[1];
    loop_ub = c_size[1];
    std::copy(&c_data[0], &c_data[loop_ub], &b_c_data[0]);
    internal::b_lusolve(a, b_c_data, b_Y_size);
  } else {
    b_a.set_size(a.size(1), a.size(0));
    loop_ub = a.size(0);
    Y_size = a.size(1);
    for (int i{0}; i < loop_ub; i++) {
      for (int i1{0}; i1 < Y_size; i1++) {
        b_a[i1 + b_a.size(0) * i] = a[i + a.size(0) * i1];
      }
    }
    loop_ub = c_size[1];
    std::copy(&c_data[0], &c_data[loop_ub], &b_c_data[0]);
    internal::qrsolve(b_a, b_c_data, c_size[1], Y_data, &Y_size);
    b_Y_size[1] = Y_size;
    if (Y_size - 1 >= 0) {
      std::copy(&Y_data[0], &Y_data[Y_size], &b_c_data[0]);
    }
  }
  ct_size[0] = 1;
  ct_size[1] = b_Y_size[1];
  loop_ub = b_Y_size[1];
  if (loop_ub - 1 >= 0) {
    std::copy(&b_c_data[0], &b_c_data[loop_ub], &ct_data[0]);
  }
  if ((a.size(0) == 0) || (a.size(1) == 0)) {
    *dt = d;
  } else {
    double Y;
    if (c_size[1] == 0) {
      b_Y_size[1] = a.size(0);
      loop_ub = a.size(0);
      std::memset(&b_c_data[0], 0,
                  static_cast<unsigned int>(loop_ub) * sizeof(double));
    } else if (a.size(0) == a.size(1)) {
      b_Y_size[0] = 1;
      b_Y_size[1] = c_size[1];
      loop_ub = c_size[1];
      std::copy(&c_data[0], &c_data[loop_ub], &b_c_data[0]);
      internal::b_lusolve(a, b_c_data, b_Y_size);
    } else {
      b_a.set_size(a.size(1), a.size(0));
      loop_ub = a.size(0);
      Y_size = a.size(1);
      for (int i{0}; i < loop_ub; i++) {
        for (int i1{0}; i1 < Y_size; i1++) {
          b_a[i1 + b_a.size(0) * i] = a[i + a.size(0) * i1];
        }
      }
      loop_ub = c_size[1];
      std::copy(&c_data[0], &c_data[loop_ub], &b_c_data[0]);
      internal::qrsolve(b_a, b_c_data, c_size[1], Y_data, &Y_size);
      b_Y_size[1] = Y_size;
      if (Y_size - 1 >= 0) {
        std::copy(&Y_data[0], &Y_data[Y_size], &b_c_data[0]);
      }
    }
    Y = 0.0;
    loop_ub = b_Y_size[1];
    for (int i{0}; i < loop_ub; i++) {
      Y += b_c_data[i] * b_data[i];
    }
    *dt = d - Y;
  }
}

} // namespace coder

//
// File trailer for lp2hp.cpp
//
// [EOF]
//
