//
// File: bilinear.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

// Include Files
#include "bilinear.h"
#include "mldivide.h"
#include "mrdivide_helper.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Declarations
static void binary_expand_op(coder::array<double, 2U> &in1,
                             const coder::array<double, 2U> &in2,
                             const coder::array<signed char, 2U> &in3,
                             const coder::array<double, 2U> &in4);

static void minus(coder::array<double, 2U> &in1,
                  const coder::array<double, 2U> &in2);

// Function Definitions
//
// Arguments    : coder::array<double, 2U> &in1
//                const coder::array<double, 2U> &in2
//                const coder::array<signed char, 2U> &in3
//                const coder::array<double, 2U> &in4
// Return Type  : void
//
static void binary_expand_op(coder::array<double, 2U> &in1,
                             const coder::array<double, 2U> &in2,
                             const coder::array<signed char, 2U> &in3,
                             const coder::array<double, 2U> &in4)
{
  coder::array<double, 2U> b_in3;
  int aux_0_1;
  int aux_1_1;
  int i;
  int i1;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  if (in4.size(0) == 1) {
    i = in3.size(0);
  } else {
    i = in4.size(0);
  }
  if (in4.size(1) == 1) {
    i1 = in3.size(1);
  } else {
    i1 = in4.size(1);
  }
  b_in3.set_size(i, i1);
  stride_0_0 = (in3.size(0) != 1);
  stride_0_1 = (in3.size(1) != 1);
  stride_1_0 = (in4.size(0) != 1);
  stride_1_1 = (in4.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  if (in4.size(1) == 1) {
    loop_ub = in3.size(1);
  } else {
    loop_ub = in4.size(1);
  }
  for (i = 0; i < loop_ub; i++) {
    int b_loop_ub;
    i1 = in4.size(0);
    if (i1 == 1) {
      b_loop_ub = in3.size(0);
    } else {
      b_loop_ub = i1;
    }
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      b_in3[i1 + b_in3.size(0) * i] =
          static_cast<double>(in3[i1 * stride_0_0 + in3.size(0) * aux_0_1]) +
          in4[i1 * stride_1_0 + in4.size(0) * aux_1_1];
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
  coder::mldivide(in2, b_in3, in1);
}

//
// Arguments    : coder::array<double, 2U> &in1
//                const coder::array<double, 2U> &in2
// Return Type  : void
//
static void minus(coder::array<double, 2U> &in1,
                  const coder::array<double, 2U> &in2)
{
  coder::array<double, 2U> b_in1;
  int aux_0_1;
  int aux_1_1;
  int b_loop_ub;
  int i;
  int i1;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  if (in2.size(0) == 1) {
    i = in1.size(0);
  } else {
    i = in2.size(0);
  }
  if (in2.size(1) == 1) {
    i1 = in1.size(1);
  } else {
    i1 = in2.size(1);
  }
  b_in1.set_size(i, i1);
  stride_0_0 = (in1.size(0) != 1);
  stride_0_1 = (in1.size(1) != 1);
  stride_1_0 = (in2.size(0) != 1);
  stride_1_1 = (in2.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  if (in2.size(1) == 1) {
    loop_ub = in1.size(1);
  } else {
    loop_ub = in2.size(1);
  }
  for (i = 0; i < loop_ub; i++) {
    i1 = in2.size(0);
    if (i1 == 1) {
      b_loop_ub = in1.size(0);
    } else {
      b_loop_ub = i1;
    }
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      b_in1[i1 + b_in1.size(0) * i] =
          in1[i1 * stride_0_0 + in1.size(0) * aux_0_1] -
          in2[i1 * stride_1_0 + in2.size(0) * aux_1_1];
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
  in1.set_size(b_in1.size(0), b_in1.size(1));
  loop_ub = b_in1.size(1);
  for (i = 0; i < loop_ub; i++) {
    b_loop_ub = b_in1.size(0);
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      in1[i1 + in1.size(0) * i] = b_in1[i1 + b_in1.size(0) * i];
    }
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &z
//                const double p_data[]
//                int p_size
//                const double k_data[]
//                const int k_size[2]
//                double fs
//                ::coder::array<double, 2U> &zd
//                double pd_data[]
//                int *pd_size
//                double kd_data[]
//                int kd_size[2]
//                double *dd
// Return Type  : void
//
namespace coder {
void bilinear(const ::coder::array<double, 2U> &z, const double p_data[],
              int p_size, const double k_data[], const int k_size[2], double fs,
              ::coder::array<double, 2U> &zd, double pd_data[], int *pd_size,
              double kd_data[], int kd_size[2], double *dd)
{
  array<double, 2U> c_I;
  array<double, 2U> r;
  array<double, 2U> t2;
  array<signed char, 2U> b_I;
  double tmp_data[1002];
  double b_d;
  int tmp_size[2];
  int d;
  int loop_ub;
  r.set_size(z.size(0), z.size(1));
  loop_ub = z.size(0) * z.size(1);
  for (int i{0}; i < loop_ub; i++) {
    r[i] = z[i] * 0.5 / 2.0;
  }
  loop_ub = static_cast<short>(z.size(0));
  d = static_cast<short>(z.size(1));
  if (loop_ub <= d) {
    d = loop_ub;
  }
  t2.set_size(static_cast<int>(static_cast<short>(z.size(0))),
              static_cast<int>(static_cast<short>(z.size(1))));
  loop_ub = static_cast<short>(z.size(0)) * static_cast<short>(z.size(1));
  for (int i{0}; i < loop_ub; i++) {
    t2[i] = 0.0;
  }
  if (d > 0) {
    for (loop_ub = 0; loop_ub < d; loop_ub++) {
      t2[loop_ub + t2.size(0) * loop_ub] = 1.0;
    }
  }
  if ((t2.size(0) == r.size(0)) && (t2.size(1) == r.size(1))) {
    loop_ub = t2.size(0) * t2.size(1);
    for (int i{0}; i < loop_ub; i++) {
      t2[i] = t2[i] - r[i];
    }
  } else {
    minus(t2, r);
  }
  loop_ub = static_cast<short>(z.size(0));
  d = static_cast<short>(z.size(1));
  if (loop_ub <= d) {
    d = loop_ub;
  }
  b_I.set_size(static_cast<int>(static_cast<short>(z.size(0))),
               static_cast<int>(static_cast<short>(z.size(1))));
  loop_ub = static_cast<short>(z.size(0)) * static_cast<short>(z.size(1));
  for (int i{0}; i < loop_ub; i++) {
    b_I[i] = 0;
  }
  if (d > 0) {
    for (loop_ub = 0; loop_ub < d; loop_ub++) {
      b_I[loop_ub + b_I.size(0) * loop_ub] = 1;
    }
  }
  if ((b_I.size(0) == r.size(0)) && (b_I.size(1) == r.size(1))) {
    c_I.set_size(b_I.size(0), b_I.size(1));
    loop_ub = b_I.size(0) * b_I.size(1);
    for (int i{0}; i < loop_ub; i++) {
      c_I[i] = static_cast<double>(b_I[i]) + r[i];
    }
    mldivide(t2, c_I, zd);
  } else {
    binary_expand_op(zd, t2, b_I, r);
  }
  mldivide(t2, p_data, p_size, pd_data, pd_size);
  for (int i{0}; i < *pd_size; i++) {
    pd_data[i] *= 0.70710678118654746;
  }
  tmp_size[0] = 1;
  tmp_size[1] = k_size[1];
  loop_ub = k_size[1];
  for (int i{0}; i < loop_ub; i++) {
    tmp_data[i] = 0.70710678118654757 * k_data[i];
  }
  internal::mrdiv(tmp_data, tmp_size, t2, kd_data, kd_size);
  internal::mrdiv(k_data, k_size, t2, tmp_data, tmp_size);
  b_d = 0.0;
  loop_ub = tmp_size[1];
  for (int i{0}; i < loop_ub; i++) {
    b_d += tmp_data[i] * p_data[i];
  }
  *dd = b_d * 0.5 / 2.0 + fs;
}

} // namespace coder

//
// File trailer for bilinear.cpp
//
// [EOF]
//
