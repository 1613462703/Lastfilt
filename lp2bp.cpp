//
// File: lp2bp.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

// Include Files
#include "lp2bp.h"
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
void lp2bp(const ::coder::array<double, 2U> &a, const double b_data[],
           int b_size, const double c_data[], const int c_size[2], double d,
           double wo, double bw, ::coder::array<double, 2U> &at,
           double bt_data[], int *bt_size, double ct_data[], int ct_size[2],
           double *dt)
{
  array<double, 2U> b_result;
  array<double, 2U> varargin_1;
  array<signed char, 2U> c_result;
  array<signed char, 2U> varargin_2;
  double q;
  int i;
  int loop_ub;
  int loop_ub_tmp;
  int result;
  short input_sizes_idx_1;
  short sizes_idx_1;
  boolean_T empty_non_axis_sizes;
  q = wo / bw;
  varargin_1.set_size(a.size(0), a.size(1));
  loop_ub = a.size(0) * a.size(1);
  for (i = 0; i < loop_ub; i++) {
    varargin_1[i] = a[i] / q;
  }
  varargin_2.set_size(c_size[1], c_size[1]);
  loop_ub_tmp = c_size[1] * c_size[1];
  for (i = 0; i < loop_ub_tmp; i++) {
    varargin_2[i] = 0;
  }
  if (c_size[1] > 0) {
    i = c_size[1];
    for (loop_ub = 0; loop_ub < i; loop_ub++) {
      varargin_2[loop_ub + varargin_2.size(0) * loop_ub] = 1;
    }
  }
  if ((varargin_1.size(0) != 0) && (varargin_1.size(1) != 0)) {
    result = varargin_1.size(0);
  } else if ((varargin_2.size(0) != 0) && (varargin_2.size(1) != 0)) {
    result = varargin_2.size(0);
  } else {
    result = varargin_1.size(0);
    if (varargin_2.size(0) > varargin_1.size(0)) {
      result = varargin_2.size(0);
    }
  }
  empty_non_axis_sizes = (result == 0);
  if (empty_non_axis_sizes ||
      ((varargin_1.size(0) != 0) && (varargin_1.size(1) != 0))) {
    input_sizes_idx_1 = static_cast<short>(varargin_1.size(1));
  } else {
    input_sizes_idx_1 = 0;
  }
  if (empty_non_axis_sizes ||
      ((varargin_2.size(0) != 0) && (varargin_2.size(1) != 0))) {
    sizes_idx_1 = static_cast<short>(varargin_2.size(1));
  } else {
    sizes_idx_1 = 0;
  }
  b_result.set_size(result, input_sizes_idx_1 + sizes_idx_1);
  loop_ub = input_sizes_idx_1;
  for (i = 0; i < loop_ub; i++) {
    for (int i1{0}; i1 < result; i1++) {
      b_result[i1 + b_result.size(0) * i] = varargin_1[i1 + result * i];
    }
  }
  loop_ub = sizes_idx_1;
  for (i = 0; i < loop_ub; i++) {
    for (int i1{0}; i1 < result; i1++) {
      b_result[i1 + b_result.size(0) * (i + input_sizes_idx_1)] =
          varargin_2[i1 + result * i];
    }
  }
  varargin_1.set_size(c_size[1], c_size[1]);
  for (i = 0; i < loop_ub_tmp; i++) {
    varargin_1[i] = 0.0;
  }
  if (c_size[1] > 0) {
    i = c_size[1];
    for (loop_ub = 0; loop_ub < i; loop_ub++) {
      varargin_1[loop_ub + varargin_1.size(0) * loop_ub] = 1.0;
    }
  }
  loop_ub = varargin_1.size(0) * varargin_1.size(1);
  for (i = 0; i < loop_ub; i++) {
    varargin_1[i] = -varargin_1[i];
  }
  if ((varargin_1.size(0) != 0) && (varargin_1.size(1) != 0)) {
    result = varargin_1.size(0);
  } else if (c_size[1] != 0) {
    result = c_size[1];
  } else {
    result = varargin_1.size(0);
  }
  empty_non_axis_sizes = (result == 0);
  if (empty_non_axis_sizes ||
      ((varargin_1.size(0) != 0) && (varargin_1.size(1) != 0))) {
    input_sizes_idx_1 = static_cast<short>(varargin_1.size(1));
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
      c_result[i1 + c_result.size(0) * i] =
          static_cast<signed char>(varargin_1[i1 + result * i]);
    }
  }
  loop_ub = sizes_idx_1;
  for (i = 0; i < loop_ub; i++) {
    for (int i1{0}; i1 < result; i1++) {
      c_result[i1 + c_result.size(0) * (i + input_sizes_idx_1)] = 0;
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
    sizes_idx_1 = static_cast<short>(c_result.size(0));
  } else {
    sizes_idx_1 = 0;
  }
  loop_ub = input_sizes_idx_1;
  loop_ub_tmp = sizes_idx_1;
  at.set_size(input_sizes_idx_1 + sizes_idx_1, result);
  for (i = 0; i < result; i++) {
    for (int i1{0}; i1 < loop_ub; i1++) {
      at[i1 + at.size(0) * i] = wo * b_result[i1 + input_sizes_idx_1 * i];
    }
  }
  for (i = 0; i < result; i++) {
    for (int i1{0}; i1 < loop_ub_tmp; i1++) {
      at[(i1 + input_sizes_idx_1) + at.size(0) * i] =
          wo * static_cast<double>(c_result[i1 + sizes_idx_1 * i]);
    }
  }
  *bt_size = b_size + c_size[1];
  for (i = 0; i < b_size; i++) {
    bt_data[i] = wo * (b_data[i] / q);
  }
  loop_ub = c_size[1];
  for (i = 0; i < loop_ub; i++) {
    bt_data[i + b_size] = wo * 0.0;
  }
  ct_size[0] = 1;
  ct_size[1] = c_size[1] + c_size[1];
  loop_ub = c_size[1];
  if (loop_ub - 1 >= 0) {
    std::copy(&c_data[0], &c_data[loop_ub], &ct_data[0]);
  }
  loop_ub = c_size[1];
  if (loop_ub - 1 >= 0) {
    std::memset(&ct_data[c_size[1]], 0,
                static_cast<unsigned int>((loop_ub + c_size[1]) - c_size[1]) *
                    sizeof(double));
  }
  *dt = d;
}

} // namespace coder

//
// File trailer for lp2bp.cpp
//
// [EOF]
//
