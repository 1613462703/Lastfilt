//
// File: zp2ss.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

// Include Files
#include "zp2ss.h"
#include "cplxpair.h"
#include "lastfilt_rtwutil.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <algorithm>
#include <cfloat>
#include <cmath>
#include <cstring>

// Function Declarations
static double rt_remd_snf(double u0, double u1);

// Function Definitions
//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_remd_snf(double u0, double u1)
{
  double y;
  if (std::isnan(u0) || std::isnan(u1) || std::isinf(u0)) {
    y = rtNaN;
  } else if (std::isinf(u1)) {
    y = u0;
  } else if ((u1 != 0.0) && (u1 != std::trunc(u1))) {
    double q;
    q = std::abs(u0 / u1);
    if (!(std::abs(q - std::floor(q + 0.5)) > DBL_EPSILON * q)) {
      y = 0.0 * u0;
    } else {
      y = std::fmod(u0, u1);
    }
  } else {
    y = std::fmod(u0, u1);
  }
  return y;
}

//
// Arguments    : const creal_T p_data[]
//                int p_size
//                double k
//                ::coder::array<double, 2U> &a
//                double b_data[]
//                int *b_size
//                double c_data[]
//                int c_size[2]
//                double *d
// Return Type  : void
//
namespace coder {
void zp2ss(const creal_T p_data[], int p_size, double k,
           ::coder::array<double, 2U> &a, double b_data[], int *b_size,
           double c_data[], int c_size[2], double *d)
{
  creal_T pf_data[501];
  creal_T vwork_data[501];
  double e_tmp_data[500];
  double absxk;
  double scale;
  double t;
  double wn;
  int dim;
  int i;
  int np;
  int vlen;
  int vstride;
  boolean_T b_tmp_data[501];
  boolean_T c_tmp_data[501];
  boolean_T d_tmp_data[501];
  boolean_T tmp_data[501];
  boolean_T oddPoles;
  for (vstride = 0; vstride < p_size; vstride++) {
    tmp_data[vstride] = std::isinf(p_data[vstride].re);
  }
  for (vstride = 0; vstride < p_size; vstride++) {
    b_tmp_data[vstride] = std::isinf(p_data[vstride].im);
  }
  for (vstride = 0; vstride < p_size; vstride++) {
    c_tmp_data[vstride] = std::isnan(p_data[vstride].re);
  }
  for (vstride = 0; vstride < p_size; vstride++) {
    d_tmp_data[vstride] = std::isnan(p_data[vstride].im);
  }
  for (vstride = 0; vstride < p_size; vstride++) {
    tmp_data[vstride] = ((!tmp_data[vstride]) && (!b_tmp_data[vstride]) &&
                         ((!c_tmp_data[vstride]) && (!d_tmp_data[vstride])));
  }
  dim = p_size - 1;
  np = 0;
  vlen = 0;
  for (i = 0; i <= dim; i++) {
    if (tmp_data[i]) {
      np++;
      pf_data[vlen] = p_data[i];
      vlen++;
    }
  }
  dim = 2;
  if (np != 1) {
    dim = 1;
  }
  oddPoles = true;
  if (np != 0) {
    if (np == 1) {
      oddPoles = internal::cplxpairv(pf_data, &np, 0.0);
    } else {
      if (dim <= 1) {
        vlen = np;
      } else {
        vlen = 1;
      }
      if (vlen != 1) {
        oddPoles = internal::cplxpairv(pf_data, &np, 0.0);
      } else {
        if (dim <= 1) {
          i = np;
        } else {
          i = 1;
        }
        vlen = i - 1;
        vstride = 1;
        for (int b_k{0}; b_k <= dim - 2; b_k++) {
          vstride *= np;
        }
        for (dim = 0; dim < vstride; dim++) {
          boolean_T paired;
          for (int b_k{0}; b_k <= vlen; b_k++) {
            vwork_data[b_k] = pf_data[dim + b_k * vstride];
          }
          paired = internal::cplxpairv(vwork_data, &i, 0.0);
          for (int b_k{0}; b_k <= vlen; b_k++) {
            pf_data[dim + b_k * vstride] = vwork_data[b_k];
          }
          if ((!oddPoles) || (!paired)) {
            oddPoles = false;
          }
        }
      }
    }
  }
  if (!oddPoles) {
    if (np == 0) {
      wn = 0.0;
    } else {
      wn = 0.0;
      if (np == 1) {
        wn = rt_hypotd_snf(pf_data[0].re, pf_data[0].im);
      } else {
        scale = 3.3121686421112381E-170;
        for (int b_k{0}; b_k < np; b_k++) {
          absxk = std::abs(pf_data[b_k].re);
          if (absxk > scale) {
            t = scale / absxk;
            wn = wn * t * t + 1.0;
            scale = absxk;
          } else {
            t = absxk / scale;
            wn += t * t;
          }
          absxk = std::abs(pf_data[b_k].im);
          if (absxk > scale) {
            t = scale / absxk;
            wn = wn * t * t + 1.0;
            scale = absxk;
          } else {
            t = absxk / scale;
            wn += t * t;
          }
        }
        wn = scale * std::sqrt(wn);
      }
    }
    wn = 1.0E+6 * static_cast<double>(np) * wn * 2.2204460492503131E-16 +
         2.2204460492503131E-16;
    dim = 2;
    if (np != 1) {
      dim = 1;
    }
    if (np != 0) {
      if (np == 1) {
        internal::cplxpairv(pf_data, &np, wn);
      } else {
        if (dim <= 1) {
          vlen = np;
        } else {
          vlen = 1;
        }
        if (vlen != 1) {
          internal::cplxpairv(pf_data, &np, wn);
        } else {
          if (dim <= 1) {
            i = np;
          } else {
            i = 1;
          }
          vlen = i - 1;
          vstride = 1;
          for (int b_k{0}; b_k <= dim - 2; b_k++) {
            vstride *= np;
          }
          for (dim = 0; dim < vstride; dim++) {
            for (int b_k{0}; b_k <= vlen; b_k++) {
              vwork_data[b_k] = pf_data[dim + b_k * vstride];
            }
            internal::cplxpairv(vwork_data, &i, wn);
            for (int b_k{0}; b_k <= vlen; b_k++) {
              pf_data[dim + b_k * vstride] = vwork_data[b_k];
            }
          }
        }
      }
    }
  }
  a.set_size(np, np);
  dim = np * np;
  for (vstride = 0; vstride < dim; vstride++) {
    a[vstride] = 0.0;
  }
  *b_size = np;
  c_size[0] = 1;
  c_size[1] = np;
  if (np - 1 >= 0) {
    std::memset(&b_data[0], 0, static_cast<unsigned int>(np) * sizeof(double));
    std::memset(&c_data[0], 0, static_cast<unsigned int>(np) * sizeof(double));
  }
  *d = 1.0;
  oddPoles = false;
  if (rt_remd_snf(static_cast<double>(np), 2.0) != 0.0) {
    a[0] = pf_data[np - 1].re;
    b_data[0] = 1.0;
    c_data[0] = 1.0;
    *d = 0.0;
    np--;
    oddPoles = true;
  }
  for (i = 1; i < np; i += 2) {
    creal_T c[3];
    creal_T x[2];
    double a1[4];
    double b_a[4];
    double b1[2];
    c[0].re = 1.0;
    c[0].im = 0.0;
    for (dim = 0; dim < 2; dim++) {
      vstride = i + dim;
      b1[dim] = vstride;
      x[dim] = pf_data[vstride - 1];
      wn = -pf_data[vstride - 1].re;
      scale = -pf_data[vstride - 1].im;
      absxk = c[dim].im;
      t = c[dim].re;
      c[dim + 1].re = wn * t - scale * absxk;
      c[dim + 1].im = wn * absxk + scale * t;
      for (int b_k{dim + 1}; b_k >= 2; b_k--) {
        wn = x[dim].re;
        scale = x[dim].im;
        c[1].re -= wn * c[0].re - scale * c[0].im;
        c[1].im -= wn * c[0].im + scale * c[0].re;
      }
    }
    dim = static_cast<int>(b1[0]) - 1;
    vlen = static_cast<int>(b1[1]) - 1;
    wn = std::sqrt(rt_hypotd_snf(pf_data[dim].re, pf_data[dim].im) *
                   rt_hypotd_snf(pf_data[vlen].re, pf_data[vlen].im));
    if (wn == 0.0) {
      wn = 1.0;
    }
    wn = 1.0 / wn;
    scale = (1.0 - -c[1].re * 0.0) / wn;
    b_a[1] = scale;
    b_a[0] = -c[1].re - scale * 0.0;
    scale = (0.0 - -c[2].re * 0.0) / wn;
    b_a[3] = scale;
    b_a[2] = -c[2].re - scale * 0.0;
    for (vstride = 0; vstride < 2; vstride++) {
      scale = b_a[vstride + 2];
      absxk = b_a[vstride];
      a1[vstride] = absxk + scale * 0.0;
      a1[vstride + 2] = absxk * 0.0 + scale * wn;
    }
    b1[1] = 0.0 / wn;
    b1[0] = 1.0 - b1[1] * 0.0;
    if (oddPoles) {
      dim = i - 1;
    } else {
      dim = i - 2;
    }
    if (dim == -1) {
      a[0] = a1[0];
      a[1] = a1[1];
      c_data[0] = 0.0;
      a[a.size(0)] = a1[2];
      a[a.size(0) + 1] = a1[3];
      c_data[1] = wn;
    } else {
      for (vstride = 0; vstride <= dim; vstride++) {
        scale = c_data[vstride];
        a[(static_cast<short>(dim + 2) + a.size(0) * vstride) - 1] =
            b1[0] * scale;
        a[(static_cast<short>(dim + 3) + a.size(0) * vstride) - 1] =
            b1[1] * scale;
      }
      a[(static_cast<short>(dim + 2) +
         a.size(0) * (static_cast<short>(dim + 2) - 1)) -
        1] = a1[0];
      a[(static_cast<short>(dim + 3) +
         a.size(0) * (static_cast<short>(dim + 2) - 1)) -
        1] = a1[1];
      a[(static_cast<short>(dim + 2) +
         a.size(0) * (static_cast<short>(dim + 3) - 1)) -
        1] = a1[2];
      a[(static_cast<short>(dim + 3) +
         a.size(0) * (static_cast<short>(dim + 3) - 1)) -
        1] = a1[3];
      vlen = dim + 1;
      for (vstride = 0; vstride <= dim; vstride++) {
        e_tmp_data[vstride] = 0.0 * c_data[vstride];
      }
      std::copy(&e_tmp_data[0], &e_tmp_data[vlen], &c_data[0]);
      c_data[static_cast<short>(dim + 2) - 1] = 0.0;
      c_data[static_cast<short>(dim + 3) - 1] = wn;
    }
    b_data[dim + 1] = b1[0] * *d;
    b_data[dim + 2] = b1[1] * *d;
    *d = 0.0;
  }
  c_size[0] = 1;
  dim = c_size[1] - 1;
  for (vstride = 0; vstride <= dim; vstride++) {
    c_data[vstride] *= k;
  }
  *d *= k;
}

} // namespace coder

//
// File trailer for zp2ss.cpp
//
// [EOF]
//
