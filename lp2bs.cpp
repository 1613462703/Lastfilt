//
// File: lp2bs.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

// Include Files
#include "lp2bs.h"
#include "inv.h"
#include "mldivide.h"
#include "mrdivide_helper.h"
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
//                double bw
//                ::coder::array<double, 2U> &at
//                double bt_data[]
//                int *bt_size
//                double ct_data[]
//                int ct_size[2]
//                double *dt
// Return Type  : void
//
namespace coder {
void lp2bs(const ::coder::array<double, 2U> &a, const double b_data[],
           int b_size, const double c_data[], const int c_size[2], double d,
           double wo, double bw, ::coder::array<double, 2U> &at,
           double bt_data[], int *bt_size, double ct_data[], int ct_size[2],
           double *dt)
{
  array<double, 2U> b_I;
  array<double, 2U> b_result;
  array<double, 2U> b_y;
  array<double, 2U> c_result;
  array<double, 2U> y;
  double tmp_data[1002];
  double a_tmp;
  int tmp_size[2];
  int i;
  int loop_ub;
  int loop_ub_tmp;
  int result;
  short input_sizes_idx_1;
  short sizes_idx_0;
  short sizes_idx_1;
  boolean_T empty_non_axis_sizes;
  a_tmp = wo / (wo / bw);
  inv(a, b_I);
  y.set_size(b_I.size(0), b_I.size(1));
  loop_ub = b_I.size(0) * b_I.size(1);
  for (i = 0; i < loop_ub; i++) {
    y[i] = a_tmp * b_I[i];
  }
  b_I.set_size(c_size[1], c_size[1]);
  loop_ub_tmp = c_size[1] * c_size[1];
  for (i = 0; i < loop_ub_tmp; i++) {
    b_I[i] = 0.0;
  }
  if (c_size[1] > 0) {
    i = c_size[1];
    for (loop_ub = 0; loop_ub < i; loop_ub++) {
      b_I[loop_ub + b_I.size(0) * loop_ub] = 1.0;
    }
  }
  b_y.set_size(b_I.size(0), b_I.size(1));
  loop_ub = b_I.size(0) * b_I.size(1);
  for (i = 0; i < loop_ub; i++) {
    b_y[i] = wo * b_I[i];
  }
  inv(a, b_I);
  sizes_idx_0 = static_cast<short>(b_I.size(0));
  sizes_idx_1 = static_cast<short>(b_I.size(1));
  b_I.set_size(c_size[1], c_size[1]);
  for (i = 0; i < loop_ub_tmp; i++) {
    b_I[i] = 0.0;
  }
  if (c_size[1] > 0) {
    i = c_size[1];
    for (loop_ub = 0; loop_ub < i; loop_ub++) {
      b_I[loop_ub + b_I.size(0) * loop_ub] = 1.0;
    }
  }
  if ((sizes_idx_0 != 0) && (sizes_idx_1 != 0)) {
    result = y.size(0);
  } else if ((b_I.size(0) != 0) && (b_I.size(1) != 0)) {
    result = b_y.size(0);
  } else {
    result = y.size(0);
    if (b_y.size(0) > y.size(0)) {
      result = b_y.size(0);
    }
  }
  empty_non_axis_sizes = (result == 0);
  if (empty_non_axis_sizes || ((sizes_idx_0 != 0) && (sizes_idx_1 != 0))) {
    input_sizes_idx_1 = static_cast<short>(y.size(1));
  } else {
    input_sizes_idx_1 = 0;
  }
  if (empty_non_axis_sizes || ((b_I.size(0) != 0) && (b_I.size(1) != 0))) {
    sizes_idx_1 = static_cast<short>(b_y.size(1));
  } else {
    sizes_idx_1 = 0;
  }
  b_result.set_size(result, input_sizes_idx_1 + sizes_idx_1);
  loop_ub = input_sizes_idx_1;
  for (i = 0; i < loop_ub; i++) {
    for (int i1{0}; i1 < result; i1++) {
      b_result[i1 + b_result.size(0) * i] = y[i1 + result * i];
    }
  }
  loop_ub = sizes_idx_1;
  for (i = 0; i < loop_ub; i++) {
    for (int i1{0}; i1 < result; i1++) {
      b_result[i1 + b_result.size(0) * (i + input_sizes_idx_1)] =
          b_y[i1 + result * i];
    }
  }
  b_I.set_size(c_size[1], c_size[1]);
  for (i = 0; i < loop_ub_tmp; i++) {
    b_I[i] = 0.0;
  }
  if (c_size[1] > 0) {
    i = c_size[1];
    for (loop_ub = 0; loop_ub < i; loop_ub++) {
      b_I[loop_ub + b_I.size(0) * loop_ub] = 1.0;
    }
  }
  y.set_size(b_I.size(0), b_I.size(1));
  loop_ub = b_I.size(0) * b_I.size(1);
  for (i = 0; i < loop_ub; i++) {
    y[i] = -wo * b_I[i];
  }
  b_I.set_size(c_size[1], c_size[1]);
  for (i = 0; i < loop_ub_tmp; i++) {
    b_I[i] = 0.0;
  }
  if (c_size[1] > 0) {
    i = c_size[1];
    for (loop_ub = 0; loop_ub < i; loop_ub++) {
      b_I[loop_ub + b_I.size(0) * loop_ub] = 1.0;
    }
  }
  if ((b_I.size(0) != 0) && (b_I.size(1) != 0)) {
    result = y.size(0);
  } else if (c_size[1] != 0) {
    result = c_size[1];
  } else {
    result = y.size(0);
  }
  empty_non_axis_sizes = (result == 0);
  if (empty_non_axis_sizes || ((b_I.size(0) != 0) && (b_I.size(1) != 0))) {
    input_sizes_idx_1 = static_cast<short>(y.size(1));
  } else {
    input_sizes_idx_1 = 0;
  }
  if (empty_non_axis_sizes || (c_size[1] != 0)) {
    sizes_idx_1 = static_cast<short>(c_size[1]);
  } else {
    sizes_idx_1 = 0;
  }
  c_result.set_size(result, input_sizes_idx_1 + sizes_idx_1);
  loop_ub = input_sizes_idx_1;
  for (i = 0; i < loop_ub; i++) {
    for (int i1{0}; i1 < result; i1++) {
      c_result[i1 + c_result.size(0) * i] = y[i1 + result * i];
    }
  }
  loop_ub = sizes_idx_1;
  for (i = 0; i < loop_ub; i++) {
    for (int i1{0}; i1 < result; i1++) {
      c_result[i1 + c_result.size(0) * (i + input_sizes_idx_1)] = 0.0;
    }
  }
  if ((b_result.size(0) != 0) && (b_result.size(1) != 0)) {
    result = b_result.size(1);
  } else if ((c_result.size(0) != 0) && (c_result.size(1) != 0)) {
    result = c_result.size(1);
  } else {
    result = b_result.size(1);
    if (c_result.size(1) > b_result.size(1)) {
      result = c_result.size(1);
    }
  }
  empty_non_axis_sizes = (result == 0);
  if (empty_non_axis_sizes ||
      ((b_result.size(0) != 0) && (b_result.size(1) != 0))) {
    input_sizes_idx_1 = static_cast<short>(b_result.size(0));
  } else {
    input_sizes_idx_1 = 0;
  }
  if (empty_non_axis_sizes ||
      ((c_result.size(0) != 0) && (c_result.size(1) != 0))) {
    sizes_idx_0 = static_cast<short>(c_result.size(0));
  } else {
    sizes_idx_0 = 0;
  }
  loop_ub_tmp = input_sizes_idx_1;
  loop_ub = sizes_idx_0;
  at.set_size(input_sizes_idx_1 + sizes_idx_0, result);
  for (i = 0; i < result; i++) {
    for (int i1{0}; i1 < loop_ub_tmp; i1++) {
      at[i1 + at.size(0) * i] = b_result[i1 + input_sizes_idx_1 * i];
    }
  }
  for (i = 0; i < result; i++) {
    for (int i1{0}; i1 < loop_ub; i1++) {
      at[(i1 + input_sizes_idx_1) + at.size(0) * i] =
          c_result[i1 + sizes_idx_0 * i];
    }
  }
  mldivide(a, b_data, b_size, tmp_data, &loop_ub_tmp);
  *bt_size = loop_ub_tmp + c_size[1];
  for (i = 0; i < loop_ub_tmp; i++) {
    bt_data[i] = -(a_tmp * tmp_data[i]);
  }
  loop_ub = c_size[1];
  if (loop_ub - 1 >= 0) {
    std::memset(
        &bt_data[loop_ub_tmp], 0,
        static_cast<unsigned int>((loop_ub + loop_ub_tmp) - loop_ub_tmp) *
            sizeof(double));
  }
  internal::mrdiv(c_data, c_size, a, tmp_data, tmp_size);
  ct_size[0] = 1;
  ct_size[1] = tmp_size[1] + c_size[1];
  loop_ub = tmp_size[1];
  if (loop_ub - 1 >= 0) {
    std::copy(&tmp_data[0], &tmp_data[loop_ub], &ct_data[0]);
  }
  loop_ub = c_size[1];
  if (loop_ub - 1 >= 0) {
    std::memset(
        &ct_data[tmp_size[1]], 0,
        static_cast<unsigned int>((loop_ub + tmp_size[1]) - tmp_size[1]) *
            sizeof(double));
  }
  if ((a.size(0) == 0) || (a.size(1) == 0)) {
    *dt = d;
  } else {
    internal::mrdiv(c_data, c_size, a, tmp_data, tmp_size);
    a_tmp = 0.0;
    loop_ub = tmp_size[1];
    for (i = 0; i < loop_ub; i++) {
      a_tmp += tmp_data[i] * b_data[i];
    }
    *dt = d - a_tmp;
  }
}

} // namespace coder

//
// File trailer for lp2bs.cpp
//
// [EOF]
//
