//
// File: butter.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

// Include Files
#include "butter.h"
#include "bilinear.h"
#include "buttap.h"
#include "eig.h"
#include "lastfilt_data.h"
#include "lp2bp.h"
#include "lp2bs.h"
#include "lp2hp.h"
#include "rt_nonfinite.h"
#include "zp2ss.h"
#include "coder_array.h"
#include "rt_defines.h"
#include <cmath>
#include <cstring>

// Function Declarations
namespace coder {
static void b_buttzeros(double n, double Wn, const creal_T p_data[], int p_size,
                        creal_T z_data[], int *z_size, double *k);

static void buttzeros(double n, double Wn, const creal_T p_data[], int p_size,
                      creal_T z_data[], int *z_size, double *k);

} // namespace coder
static double rt_atan2d_snf(double u0, double u1);

static double rt_powd_snf(double u0, double u1);

// Function Definitions
//
// Arguments    : double n
//                double Wn
//                const creal_T p_data[]
//                int p_size
//                creal_T z_data[]
//                int *z_size
//                double *k
// Return Type  : void
//
namespace coder {
static void b_buttzeros(double n, double Wn, const creal_T p_data[], int p_size,
                        creal_T z_data[], int *z_size, double *k)
{
  creal_T x_data[1002];
  double y_data[1000];
  double b_im;
  double b_re_tmp;
  double b_y_re;
  double im;
  double r;
  double re_tmp;
  double y_re;
  int loop_ub;
  boolean_T exitg1;
  boolean_T y;
  r = 2.0 * n - 1.0;
  if (std::isnan(r)) {
    *z_size = 1;
    y_data[0] = rtNaN;
  } else if (r < 0.0) {
    *z_size = 0;
  } else {
    *z_size = static_cast<int>(r) + 1;
    loop_ub = static_cast<int>(r);
    for (int i{0}; i <= loop_ub; i++) {
      y_data[i] = i;
    }
  }
  r = 2.0 * rt_atan2d_snf(Wn, 4.0);
  y_re = r * 0.0;
  loop_ub = *z_size - 1;
  for (int i{0}; i <= loop_ub; i++) {
    y_data[i] = rt_powd_snf(-1.0, y_data[i]);
  }
  for (int i{0}; i < *z_size; i++) {
    re_tmp = y_data[i];
    z_data[i].re = re_tmp * y_re;
    z_data[i].im = re_tmp * r;
  }
  for (loop_ub = 0; loop_ub < *z_size; loop_ub++) {
    re_tmp = z_data[loop_ub].im;
    if (re_tmp == 0.0) {
      z_data[loop_ub].re = std::exp(z_data[loop_ub].re);
      z_data[loop_ub].im = 0.0;
    } else if (std::isinf(re_tmp) && std::isinf(z_data[loop_ub].re) &&
               (z_data[loop_ub].re < 0.0)) {
      z_data[loop_ub].re = 0.0;
      z_data[loop_ub].im = 0.0;
    } else {
      r = std::exp(z_data[loop_ub].re / 2.0);
      z_data[loop_ub].re = r * (r * std::cos(re_tmp));
      re_tmp = r * (r * std::sin(re_tmp));
      z_data[loop_ub].im = re_tmp;
    }
  }
  for (int i{0}; i < p_size; i++) {
    x_data[i].re = 1.0 - p_data[i].re;
    x_data[i].im = 0.0 - p_data[i].im;
  }
  if (p_size == 0) {
    y_re = 1.0;
    im = 0.0;
  } else {
    y_re = x_data[0].re;
    im = x_data[0].im;
    for (loop_ub = 2; loop_ub <= p_size; loop_ub++) {
      re_tmp = x_data[loop_ub - 1].im;
      b_re_tmp = x_data[loop_ub - 1].re;
      r = y_re * b_re_tmp - im * re_tmp;
      im = y_re * re_tmp + im * b_re_tmp;
      y_re = r;
    }
  }
  for (int i{0}; i < *z_size; i++) {
    x_data[i].re = 1.0 - z_data[i].re;
    x_data[i].im = 0.0 - z_data[i].im;
  }
  if (*z_size == 0) {
    b_y_re = 1.0;
    b_im = 0.0;
  } else {
    b_y_re = x_data[0].re;
    b_im = x_data[0].im;
    for (loop_ub = 2; loop_ub <= *z_size; loop_ub++) {
      re_tmp = x_data[loop_ub - 1].im;
      b_re_tmp = x_data[loop_ub - 1].re;
      r = b_y_re * b_re_tmp - b_im * re_tmp;
      b_im = b_y_re * re_tmp + b_im * b_re_tmp;
      b_y_re = r;
    }
  }
  if (b_im == 0.0) {
    if (im == 0.0) {
      *k = y_re / b_y_re;
    } else if (y_re == 0.0) {
      *k = 0.0;
    } else {
      *k = y_re / b_y_re;
    }
  } else if (b_y_re == 0.0) {
    if (y_re == 0.0) {
      *k = im / b_im;
    } else if (im == 0.0) {
      *k = 0.0;
    } else {
      *k = im / b_im;
    }
  } else {
    r = std::abs(b_y_re);
    re_tmp = std::abs(b_im);
    if (r > re_tmp) {
      r = b_im / b_y_re;
      *k = (y_re + r * im) / (b_y_re + r * b_im);
    } else if (re_tmp == r) {
      if (b_y_re > 0.0) {
        b_re_tmp = 0.5;
      } else {
        b_re_tmp = -0.5;
      }
      if (b_im > 0.0) {
        re_tmp = 0.5;
      } else {
        re_tmp = -0.5;
      }
      *k = (y_re * b_re_tmp + im * re_tmp) / r;
    } else {
      r = b_y_re / b_im;
      *k = (r * y_re + im) / (b_im + r * b_y_re);
    }
  }
  for (int i{0}; i < *z_size; i++) {
    y_data[i] = z_data[i].im;
  }
  y = false;
  loop_ub = 0;
  exitg1 = false;
  while ((!exitg1) && (loop_ub + 1 <= *z_size)) {
    if ((y_data[loop_ub] == 0.0) || std::isnan(y_data[loop_ub])) {
      loop_ub++;
    } else {
      y = true;
      exitg1 = true;
    }
  }
  if (!y) {
    for (int i{0}; i < *z_size; i++) {
      z_data[i].im = 0.0;
    }
  }
}

//
// Arguments    : double n
//                double Wn
//                const creal_T p_data[]
//                int p_size
//                creal_T z_data[]
//                int *z_size
//                double *k
// Return Type  : void
//
static void buttzeros(double n, double Wn, const creal_T p_data[], int p_size,
                      creal_T z_data[], int *z_size, double *k)
{
  creal_T x_data[1002];
  double im;
  double r;
  double re_tmp;
  double y_re;
  double zWn_im;
  double zWn_re;
  double zWn_re_tmp;
  int loop_ub;
  signed char b_x_data[1000];
  boolean_T exitg1;
  boolean_T y;
  *z_size = static_cast<int>(n) + static_cast<int>(n);
  loop_ub = static_cast<int>(n);
  for (int i{0}; i < loop_ub; i++) {
    z_data[i].re = 1.0;
    z_data[i].im = 0.0;
  }
  loop_ub = static_cast<int>(n);
  for (int i{0}; i < loop_ub; i++) {
    int i1;
    i1 = i + static_cast<int>(n);
    z_data[i1].re = -1.0;
    z_data[i1].im = 0.0;
  }
  zWn_re_tmp = 2.0 * rt_atan2d_snf(Wn, 4.0);
  zWn_re = zWn_re_tmp * 0.0;
  if (zWn_re_tmp == 0.0) {
    zWn_re = std::exp(zWn_re);
    zWn_im = 0.0;
  } else {
    r = std::exp(zWn_re / 2.0);
    zWn_re = r * (r * std::cos(zWn_re_tmp));
    zWn_im = r * (r * std::sin(zWn_re_tmp));
  }
  for (int i{0}; i < p_size; i++) {
    x_data[i].re = zWn_re - p_data[i].re;
    x_data[i].im = zWn_im - p_data[i].im;
  }
  if (p_size == 0) {
    y_re = 1.0;
    im = 0.0;
  } else {
    y_re = x_data[0].re;
    im = x_data[0].im;
    for (loop_ub = 2; loop_ub <= p_size; loop_ub++) {
      r = x_data[loop_ub - 1].im;
      re_tmp = x_data[loop_ub - 1].re;
      zWn_re_tmp = y_re * re_tmp - im * r;
      im = y_re * r + im * re_tmp;
      y_re = zWn_re_tmp;
    }
  }
  for (int i{0}; i < *z_size; i++) {
    x_data[i].re = zWn_re - z_data[i].re;
    x_data[i].im = zWn_im - z_data[i].im;
  }
  if (*z_size == 0) {
    zWn_re = 1.0;
    zWn_im = 0.0;
  } else {
    zWn_re = x_data[0].re;
    zWn_im = x_data[0].im;
    for (loop_ub = 2; loop_ub <= *z_size; loop_ub++) {
      r = x_data[loop_ub - 1].im;
      re_tmp = x_data[loop_ub - 1].re;
      zWn_re_tmp = zWn_re * re_tmp - zWn_im * r;
      zWn_im = zWn_re * r + zWn_im * re_tmp;
      zWn_re = zWn_re_tmp;
    }
  }
  if (zWn_im == 0.0) {
    if (im == 0.0) {
      *k = y_re / zWn_re;
    } else if (y_re == 0.0) {
      *k = 0.0;
    } else {
      *k = y_re / zWn_re;
    }
  } else if (zWn_re == 0.0) {
    if (y_re == 0.0) {
      *k = im / zWn_im;
    } else if (im == 0.0) {
      *k = 0.0;
    } else {
      *k = im / zWn_im;
    }
  } else {
    zWn_re_tmp = std::abs(zWn_re);
    r = std::abs(zWn_im);
    if (zWn_re_tmp > r) {
      zWn_re_tmp = zWn_im / zWn_re;
      *k = (y_re + zWn_re_tmp * im) / (zWn_re + zWn_re_tmp * zWn_im);
    } else if (r == zWn_re_tmp) {
      if (zWn_re > 0.0) {
        r = 0.5;
      } else {
        r = -0.5;
      }
      if (zWn_im > 0.0) {
        zWn_re = 0.5;
      } else {
        zWn_re = -0.5;
      }
      *k = (y_re * r + im * zWn_re) / zWn_re_tmp;
    } else {
      zWn_re_tmp = zWn_re / zWn_im;
      *k = (zWn_re_tmp * y_re + im) / (zWn_im + zWn_re_tmp * zWn_re);
    }
  }
  for (int i{0}; i < *z_size; i++) {
    b_x_data[i] = static_cast<signed char>(z_data[i].im);
  }
  y = false;
  loop_ub = 1;
  exitg1 = false;
  while ((!exitg1) && (loop_ub <= *z_size)) {
    if (b_x_data[loop_ub - 1] != 0) {
      y = true;
      exitg1 = true;
    } else {
      loop_ub++;
    }
  }
  if (!y) {
    for (int i{0}; i < *z_size; i++) {
      z_data[i].im = 0.0;
    }
  }
}

//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
} // namespace coder
static double rt_atan2d_snf(double u0, double u1)
{
  double y;
  if (std::isnan(u0) || std::isnan(u1)) {
    y = rtNaN;
  } else if (std::isinf(u0) && std::isinf(u1)) {
    int i;
    int i1;
    if (u0 > 0.0) {
      i = 1;
    } else {
      i = -1;
    }
    if (u1 > 0.0) {
      i1 = 1;
    } else {
      i1 = -1;
    }
    y = std::atan2(static_cast<double>(i), static_cast<double>(i1));
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = std::atan2(u0, u1);
  }
  return y;
}

//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_powd_snf(double u0, double u1)
{
  double y;
  if (std::isnan(u0) || std::isnan(u1)) {
    y = rtNaN;
  } else {
    double d;
    double d1;
    d = std::abs(u0);
    d1 = std::abs(u1);
    if (std::isinf(u1)) {
      if (d == 1.0) {
        y = 1.0;
      } else if (d > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = std::sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > std::floor(u1))) {
      y = rtNaN;
    } else {
      y = std::pow(u0, u1);
    }
  }
  return y;
}

//
// Arguments    : double n
//                double Wn
//                double varargout_1_data[]
//                int varargout_1_size[2]
//                double varargout_2_data[]
//                int varargout_2_size[2]
// Return Type  : void
//
namespace coder {
void b_butter(double n, double Wn, double varargout_1_data[],
              int varargout_1_size[2], double varargout_2_data[],
              int varargout_2_size[2])
{
  array<double, 2U> a;
  array<double, 2U> ad;
  array<double, 2U> b_ad;
  creal_T b_c_data[1003];
  creal_T p_data[1002];
  creal_T x_data[1002];
  creal_T ps_data[501];
  cuint8_T z_data[500];
  double b_bd_data[1002];
  double b_cd_data[1002];
  double b_data[501];
  double bd_data[501];
  double c_data[501];
  double cd_data[501];
  double b_a;
  double b_re_tmp;
  double d;
  double dd;
  double ks;
  double re_tmp;
  int c_size[2];
  int cd_size[2];
  int b_size;
  int bd_size;
  int c_size_idx_1;
  int loop_ub_tmp;
  int ps_size;
  buttap(n, ps_data, &ps_size, &ks);
  zp2ss(ps_data, ps_size, ks, a, b_data, &b_size, c_data, c_size, &d);
  lp2hp(a, b_data, b_size, c_data, c_size, d,
        4.0 * std::tan(3.1415926535897931 * Wn / 2.0), ad, bd_data, &bd_size,
        cd_data, cd_size, &dd);
  bilinear(ad, bd_data, bd_size, cd_data, cd_size, dd, b_ad, b_bd_data,
           &ps_size, b_cd_data, c_size, &ks);
  eig(b_ad, p_data, &bd_size);
  loop_ub_tmp = static_cast<int>(n);
  for (b_size = 0; b_size < bd_size; b_size++) {
    x_data[b_size].re = p_data[b_size].re + 1.0;
    x_data[b_size].im = p_data[b_size].im;
  }
  if (bd_size == 0) {
    ks = 1.0;
  } else {
    ks = x_data[0].re;
    dd = x_data[0].im;
    for (ps_size = 2; ps_size <= bd_size; ps_size++) {
      re_tmp = x_data[ps_size - 1].im;
      b_re_tmp = x_data[ps_size - 1].re;
      d = ks * b_re_tmp - dd * re_tmp;
      dd = ks * re_tmp + dd * b_re_tmp;
      ks = d;
    }
  }
  b_a = ks / rt_powd_snf(2.0, n);
  for (b_size = 0; b_size < loop_ub_tmp; b_size++) {
    z_data[b_size].re = 1U;
    z_data[b_size].im = 0U;
  }
  c_size_idx_1 = bd_size + 1;
  b_c_data[0].re = 1.0;
  b_c_data[0].im = 0.0;
  for (b_size = 0; b_size < bd_size; b_size++) {
    double p_im_tmp;
    dd = p_data[b_size].re;
    p_im_tmp = p_data[b_size].im;
    re_tmp = b_c_data[b_size].im;
    b_re_tmp = b_c_data[b_size].re;
    b_c_data[b_size + 1].re = -dd * b_re_tmp - -p_im_tmp * re_tmp;
    b_c_data[b_size + 1].im = -dd * re_tmp + -p_im_tmp * b_re_tmp;
    for (ps_size = b_size + 1; ps_size >= 2; ps_size--) {
      ks = b_c_data[ps_size - 2].im;
      d = b_c_data[ps_size - 2].re;
      b_c_data[ps_size - 1].re -= dd * d - p_im_tmp * ks;
      b_c_data[ps_size - 1].im -= dd * ks + p_im_tmp * d;
    }
  }
  varargout_2_size[0] = 1;
  varargout_2_size[1] = bd_size + 1;
  for (b_size = 0; b_size < c_size_idx_1; b_size++) {
    varargout_2_data[b_size] = b_c_data[b_size].re;
  }
  c_size_idx_1 = static_cast<int>(n) + 1;
  b_c_data[0].re = 1.0;
  b_c_data[0].im = 0.0;
  for (b_size = 0; b_size < loop_ub_tmp; b_size++) {
    signed char z_im_tmp;
    z_im_tmp = static_cast<signed char>(z_data[b_size].im);
    re_tmp = b_c_data[b_size].im;
    b_re_tmp = b_c_data[b_size].re;
    b_c_data[b_size + 1].re =
        -b_re_tmp - -static_cast<double>(z_im_tmp) * re_tmp;
    b_c_data[b_size + 1].im =
        -re_tmp + -static_cast<double>(z_im_tmp) * b_re_tmp;
    for (ps_size = b_size + 1; ps_size >= 2; ps_size--) {
      ks = b_c_data[ps_size - 2].re;
      d = b_c_data[ps_size - 2].im;
      b_c_data[ps_size - 1].re -= ks - static_cast<double>(z_im_tmp) * d;
      b_c_data[ps_size - 1].im -= d + static_cast<double>(z_im_tmp) * ks;
    }
  }
  ps_size = bd_size - static_cast<int>(n);
  varargout_1_size[0] = 1;
  varargout_1_size[1] = (ps_size + static_cast<int>(n)) + 1;
  if (ps_size - 1 >= 0) {
    std::memset(&varargout_1_data[0], 0,
                static_cast<unsigned int>(ps_size) * sizeof(double));
  }
  for (b_size = 0; b_size < c_size_idx_1; b_size++) {
    varargout_1_data[b_size + ps_size] = b_a * b_c_data[b_size].re;
  }
}

//
// Arguments    : double n
//                const double Wn[2]
//                double varargout_1_data[]
//                int varargout_1_size[2]
//                double varargout_2_data[]
//                int varargout_2_size[2]
// Return Type  : void
//
void b_butter(double n, const double Wn[2], double varargout_1_data[],
              int varargout_1_size[2], double varargout_2_data[],
              int varargout_2_size[2])
{
  array<double, 2U> a;
  array<double, 2U> ad;
  array<double, 2U> b_ad;
  creal_T b_c_data[1003];
  creal_T p_data[1002];
  creal_T z_data[1000];
  creal_T ps_data[501];
  double b_bd_data[1002];
  double b_cd_data[1002];
  double bd_data[1002];
  double cd_data[1002];
  double b_data[501];
  double c_data[501];
  double Wn1;
  double d;
  double dd;
  double ks;
  double u_idx_0;
  double u_idx_1;
  int c_size[2];
  int cd_size[2];
  int b_size;
  int bd_size;
  int c_size_idx_1;
  int ps_size;
  int z_size;
  u_idx_0 = 4.0 * std::tan(3.1415926535897931 * Wn[0] / 2.0);
  u_idx_1 = 4.0 * std::tan(3.1415926535897931 * Wn[1] / 2.0);
  buttap(n, ps_data, &ps_size, &ks);
  zp2ss(ps_data, ps_size, ks, a, b_data, &b_size, c_data, c_size, &d);
  Wn1 = std::sqrt(u_idx_0 * u_idx_1);
  lp2bs(a, b_data, b_size, c_data, c_size, d, Wn1, u_idx_1 - u_idx_0, ad,
        bd_data, &bd_size, cd_data, cd_size, &dd);
  bilinear(ad, bd_data, bd_size, cd_data, cd_size, dd, b_ad, b_bd_data,
           &ps_size, b_cd_data, c_size, &ks);
  eig(b_ad, p_data, &bd_size);
  b_buttzeros(n, Wn1, p_data, bd_size, z_data, &z_size, &dd);
  c_size_idx_1 = bd_size + 1;
  b_c_data[0].re = 1.0;
  b_c_data[0].im = 0.0;
  for (ps_size = 0; ps_size < bd_size; ps_size++) {
    u_idx_1 = p_data[ps_size].re;
    d = p_data[ps_size].im;
    ks = b_c_data[ps_size].im;
    u_idx_0 = b_c_data[ps_size].re;
    b_c_data[ps_size + 1].re = -u_idx_1 * u_idx_0 - -d * ks;
    b_c_data[ps_size + 1].im = -u_idx_1 * ks + -d * u_idx_0;
    for (b_size = ps_size + 1; b_size >= 2; b_size--) {
      ks = b_c_data[b_size - 2].im;
      u_idx_0 = b_c_data[b_size - 2].re;
      b_c_data[b_size - 1].re -= u_idx_1 * u_idx_0 - d * ks;
      b_c_data[b_size - 1].im -= u_idx_1 * ks + d * u_idx_0;
    }
  }
  varargout_2_size[0] = 1;
  varargout_2_size[1] = bd_size + 1;
  for (b_size = 0; b_size < c_size_idx_1; b_size++) {
    varargout_2_data[b_size] = b_c_data[b_size].re;
  }
  c_size_idx_1 = z_size + 1;
  b_c_data[0].re = 1.0;
  b_c_data[0].im = 0.0;
  for (ps_size = 0; ps_size < z_size; ps_size++) {
    u_idx_1 = z_data[ps_size].re;
    d = z_data[ps_size].im;
    ks = b_c_data[ps_size].im;
    u_idx_0 = b_c_data[ps_size].re;
    b_c_data[ps_size + 1].re = -u_idx_1 * u_idx_0 - -d * ks;
    b_c_data[ps_size + 1].im = -u_idx_1 * ks + -d * u_idx_0;
    for (b_size = ps_size + 1; b_size >= 2; b_size--) {
      ks = b_c_data[b_size - 2].im;
      u_idx_0 = b_c_data[b_size - 2].re;
      b_c_data[b_size - 1].re -= u_idx_1 * u_idx_0 - d * ks;
      b_c_data[b_size - 1].im -= u_idx_1 * ks + d * u_idx_0;
    }
  }
  ps_size = bd_size - z_size;
  varargout_1_size[0] = 1;
  varargout_1_size[1] = (ps_size + z_size) + 1;
  if (ps_size - 1 >= 0) {
    std::memset(&varargout_1_data[0], 0,
                static_cast<unsigned int>(ps_size) * sizeof(double));
  }
  for (b_size = 0; b_size < c_size_idx_1; b_size++) {
    varargout_1_data[b_size + ps_size] = dd * b_c_data[b_size].re;
  }
}

//
// Arguments    : double n
//                double Wn
//                double varargout_1_data[]
//                int varargout_1_size[2]
//                double varargout_2_data[]
//                int varargout_2_size[2]
// Return Type  : void
//
void butter(double n, double Wn, double varargout_1_data[],
            int varargout_1_size[2], double varargout_2_data[],
            int varargout_2_size[2])
{
  array<double, 2U> a;
  array<double, 2U> ad;
  array<double, 2U> wo;
  creal_T b_c_data[1003];
  creal_T p_data[1002];
  creal_T x_data[1002];
  creal_T ps_data[501];
  cint8_T z_data[500];
  double bd_data[1002];
  double cd_data[1002];
  double wo_data[1002];
  double b_data[501];
  double c_data[501];
  double b_a;
  double b_re_tmp;
  double d;
  double im;
  double ks;
  double re_tmp;
  int c_size[2];
  int cd_size[2];
  int b_size;
  int c_size_idx_1;
  int loop_ub_tmp;
  int p_size;
  int ps_size;
  int z_im_tmp;
  signed char b_x_data[1000];
  boolean_T exitg1;
  boolean_T y;
  buttap(n, ps_data, &ps_size, &ks);
  zp2ss(ps_data, ps_size, ks, a, b_data, &b_size, c_data, c_size, &d);
  ks = 4.0 * std::tan(3.1415926535897931 * Wn / 2.0);
  wo.set_size(a.size(0), a.size(1));
  ps_size = a.size(0) * a.size(1);
  for (z_im_tmp = 0; z_im_tmp < ps_size; z_im_tmp++) {
    wo[z_im_tmp] = ks * a[z_im_tmp];
  }
  for (z_im_tmp = 0; z_im_tmp < b_size; z_im_tmp++) {
    wo_data[z_im_tmp] = ks * b_data[z_im_tmp];
  }
  bilinear(wo, wo_data, b_size, c_data, c_size, d, ad, bd_data, &ps_size,
           cd_data, cd_size, &ks);
  eig(ad, p_data, &p_size);
  loop_ub_tmp = static_cast<int>(n);
  for (z_im_tmp = 0; z_im_tmp < loop_ub_tmp; z_im_tmp++) {
    z_data[z_im_tmp].re = -1;
    z_data[z_im_tmp].im = 0;
  }
  for (z_im_tmp = 0; z_im_tmp < p_size; z_im_tmp++) {
    x_data[z_im_tmp].re = 1.0 - p_data[z_im_tmp].re;
    x_data[z_im_tmp].im = 0.0 - p_data[z_im_tmp].im;
  }
  if (p_size == 0) {
    ks = 1.0;
  } else {
    ks = x_data[0].re;
    im = x_data[0].im;
    for (ps_size = 2; ps_size <= p_size; ps_size++) {
      re_tmp = x_data[ps_size - 1].im;
      b_re_tmp = x_data[ps_size - 1].re;
      d = ks * b_re_tmp - im * re_tmp;
      im = ks * re_tmp + im * b_re_tmp;
      ks = d;
    }
  }
  b_a = ks / rt_powd_snf(2.0, n);
  for (z_im_tmp = 0; z_im_tmp < loop_ub_tmp; z_im_tmp++) {
    b_x_data[z_im_tmp] = z_data[z_im_tmp].im;
  }
  y = false;
  ps_size = 1;
  exitg1 = false;
  while ((!exitg1) && (ps_size <= static_cast<int>(n))) {
    if (b_x_data[ps_size - 1] != 0) {
      y = true;
      exitg1 = true;
    } else {
      ps_size++;
    }
  }
  if (!y) {
    for (z_im_tmp = 0; z_im_tmp < loop_ub_tmp; z_im_tmp++) {
      z_data[z_im_tmp].re = -1;
      z_data[z_im_tmp].im = 0;
    }
  }
  c_size_idx_1 = p_size + 1;
  b_c_data[0].re = 1.0;
  b_c_data[0].im = 0.0;
  for (b_size = 0; b_size < p_size; b_size++) {
    double p_im_tmp;
    im = p_data[b_size].re;
    p_im_tmp = p_data[b_size].im;
    re_tmp = b_c_data[b_size].im;
    b_re_tmp = b_c_data[b_size].re;
    b_c_data[b_size + 1].re = -im * b_re_tmp - -p_im_tmp * re_tmp;
    b_c_data[b_size + 1].im = -im * re_tmp + -p_im_tmp * b_re_tmp;
    for (ps_size = b_size + 1; ps_size >= 2; ps_size--) {
      ks = b_c_data[ps_size - 2].im;
      d = b_c_data[ps_size - 2].re;
      b_c_data[ps_size - 1].re -= im * d - p_im_tmp * ks;
      b_c_data[ps_size - 1].im -= im * ks + p_im_tmp * d;
    }
  }
  varargout_2_size[0] = 1;
  varargout_2_size[1] = p_size + 1;
  for (z_im_tmp = 0; z_im_tmp < c_size_idx_1; z_im_tmp++) {
    varargout_2_data[z_im_tmp] = b_c_data[z_im_tmp].re;
  }
  c_size_idx_1 = static_cast<int>(n) + 1;
  b_c_data[0].re = 1.0;
  b_c_data[0].im = 0.0;
  for (b_size = 0; b_size < loop_ub_tmp; b_size++) {
    z_im_tmp = z_data[b_size].im;
    re_tmp = b_c_data[b_size].re;
    b_re_tmp = b_c_data[b_size].im;
    b_c_data[b_size + 1].re =
        re_tmp - -static_cast<double>(z_im_tmp) * b_re_tmp;
    b_c_data[b_size + 1].im =
        b_re_tmp + -static_cast<double>(z_im_tmp) * re_tmp;
    for (ps_size = b_size + 1; ps_size >= 2; ps_size--) {
      ks = b_c_data[ps_size - 2].im;
      d = b_c_data[ps_size - 2].re;
      b_c_data[ps_size - 1].re -= -d - static_cast<double>(z_im_tmp) * ks;
      b_c_data[ps_size - 1].im -= -ks + static_cast<double>(z_im_tmp) * d;
    }
  }
  ps_size = p_size - static_cast<int>(n);
  varargout_1_size[0] = 1;
  varargout_1_size[1] = (ps_size + static_cast<int>(n)) + 1;
  if (ps_size - 1 >= 0) {
    std::memset(&varargout_1_data[0], 0,
                static_cast<unsigned int>(ps_size) * sizeof(double));
  }
  for (z_im_tmp = 0; z_im_tmp < c_size_idx_1; z_im_tmp++) {
    varargout_1_data[z_im_tmp + ps_size] = b_a * b_c_data[z_im_tmp].re;
  }
}

//
// Arguments    : double n
//                const double Wn[2]
//                double varargout_1_data[]
//                int varargout_1_size[2]
//                double varargout_2_data[]
//                int varargout_2_size[2]
// Return Type  : void
//
void butter(double n, const double Wn[2], double varargout_1_data[],
            int varargout_1_size[2], double varargout_2_data[],
            int varargout_2_size[2])
{
  array<double, 2U> a;
  array<double, 2U> ad;
  array<double, 2U> b_ad;
  creal_T b_c_data[1003];
  creal_T p_data[1002];
  creal_T z_data[1000];
  creal_T ps_data[501];
  double b_bd_data[1002];
  double b_cd_data[1002];
  double bd_data[1002];
  double cd_data[1002];
  double b_data[501];
  double c_data[501];
  double Wn1;
  double d;
  double dd;
  double ks;
  double u_idx_0;
  double u_idx_1;
  int c_size[2];
  int cd_size[2];
  int b_size;
  int bd_size;
  int c_size_idx_1;
  int ps_size;
  int z_size;
  u_idx_0 = 4.0 * std::tan(3.1415926535897931 * Wn[0] / 2.0);
  u_idx_1 = 4.0 * std::tan(3.1415926535897931 * Wn[1] / 2.0);
  buttap(n, ps_data, &ps_size, &ks);
  zp2ss(ps_data, ps_size, ks, a, b_data, &b_size, c_data, c_size, &d);
  Wn1 = std::sqrt(u_idx_0 * u_idx_1);
  lp2bp(a, b_data, b_size, c_data, c_size, d, Wn1, u_idx_1 - u_idx_0, ad,
        bd_data, &bd_size, cd_data, cd_size, &dd);
  bilinear(ad, bd_data, bd_size, cd_data, cd_size, dd, b_ad, b_bd_data,
           &ps_size, b_cd_data, c_size, &ks);
  eig(b_ad, p_data, &bd_size);
  buttzeros(n, Wn1, p_data, bd_size, z_data, &z_size, &dd);
  c_size_idx_1 = bd_size + 1;
  b_c_data[0].re = 1.0;
  b_c_data[0].im = 0.0;
  for (ps_size = 0; ps_size < bd_size; ps_size++) {
    u_idx_1 = p_data[ps_size].re;
    d = p_data[ps_size].im;
    ks = b_c_data[ps_size].im;
    u_idx_0 = b_c_data[ps_size].re;
    b_c_data[ps_size + 1].re = -u_idx_1 * u_idx_0 - -d * ks;
    b_c_data[ps_size + 1].im = -u_idx_1 * ks + -d * u_idx_0;
    for (b_size = ps_size + 1; b_size >= 2; b_size--) {
      ks = b_c_data[b_size - 2].im;
      u_idx_0 = b_c_data[b_size - 2].re;
      b_c_data[b_size - 1].re -= u_idx_1 * u_idx_0 - d * ks;
      b_c_data[b_size - 1].im -= u_idx_1 * ks + d * u_idx_0;
    }
  }
  varargout_2_size[0] = 1;
  varargout_2_size[1] = bd_size + 1;
  for (b_size = 0; b_size < c_size_idx_1; b_size++) {
    varargout_2_data[b_size] = b_c_data[b_size].re;
  }
  c_size_idx_1 = z_size + 1;
  b_c_data[0].re = 1.0;
  b_c_data[0].im = 0.0;
  for (ps_size = 0; ps_size < z_size; ps_size++) {
    u_idx_1 = z_data[ps_size].re;
    d = z_data[ps_size].im;
    ks = b_c_data[ps_size].im;
    u_idx_0 = b_c_data[ps_size].re;
    b_c_data[ps_size + 1].re = -u_idx_1 * u_idx_0 - -d * ks;
    b_c_data[ps_size + 1].im = -u_idx_1 * ks + -d * u_idx_0;
    for (b_size = ps_size + 1; b_size >= 2; b_size--) {
      ks = b_c_data[b_size - 2].im;
      u_idx_0 = b_c_data[b_size - 2].re;
      b_c_data[b_size - 1].re -= u_idx_1 * u_idx_0 - d * ks;
      b_c_data[b_size - 1].im -= u_idx_1 * ks + d * u_idx_0;
    }
  }
  ps_size = bd_size - z_size;
  varargout_1_size[0] = 1;
  varargout_1_size[1] = (ps_size + z_size) + 1;
  if (ps_size - 1 >= 0) {
    std::memset(&varargout_1_data[0], 0,
                static_cast<unsigned int>(ps_size) * sizeof(double));
  }
  for (b_size = 0; b_size < c_size_idx_1; b_size++) {
    varargout_1_data[b_size + ps_size] = dd * b_c_data[b_size].re;
  }
}

} // namespace coder

//
// File trailer for butter.cpp
//
// [EOF]
//
