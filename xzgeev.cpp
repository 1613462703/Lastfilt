//
// File: xzgeev.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

// Include Files
#include "xzgeev.h"
#include "lastfilt_rtwutil.h"
#include "rt_nonfinite.h"
#include "xzggbal.h"
#include "xzhgeqz.h"
#include "xzlartg.h"
#include "coder_array.h"
#include <cmath>
#include <cstring>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &A
//                int *info
//                creal_T alpha1_data[]
//                int *alpha1_size
//                creal_T beta1_data[]
//                int *beta1_size
// Return Type  : void
//
namespace coder {
namespace internal {
namespace reflapack {
void xzgeev(const ::coder::array<double, 2U> &A, int *info,
            creal_T alpha1_data[], int *alpha1_size, creal_T beta1_data[],
            int *beta1_size)
{
  array<creal_T, 2U> At;
  creal_T s;
  double absxk;
  int rscale_data[1002];
  int ihi;
  int ilo;
  int n;
  At.set_size(A.size(0), A.size(1));
  n = A.size(0) * A.size(1);
  for (int jcol{0}; jcol < n; jcol++) {
    At[jcol].re = A[jcol];
    At[jcol].im = 0.0;
  }
  *info = 0;
  *alpha1_size = At.size(0);
  n = At.size(0);
  if (n - 1 >= 0) {
    std::memset(&alpha1_data[0], 0,
                static_cast<unsigned int>(n) * sizeof(creal_T));
  }
  *beta1_size = At.size(0);
  n = At.size(0);
  if (n - 1 >= 0) {
    std::memset(&beta1_data[0], 0,
                static_cast<unsigned int>(n) * sizeof(creal_T));
  }
  if ((At.size(0) != 0) && (At.size(1) != 0)) {
    double anrm;
    boolean_T exitg1;
    anrm = 0.0;
    n = 0;
    exitg1 = false;
    while ((!exitg1) && (n <= At.size(0) * At.size(1) - 1)) {
      absxk = rt_hypotd_snf(At[n].re, At[n].im);
      if (std::isnan(absxk)) {
        anrm = rtNaN;
        exitg1 = true;
      } else {
        if (absxk > anrm) {
          anrm = absxk;
        }
        n++;
      }
    }
    if (std::isinf(anrm) || std::isnan(anrm)) {
      *alpha1_size = At.size(0);
      n = At.size(0);
      for (int jcol{0}; jcol < n; jcol++) {
        alpha1_data[jcol].re = rtNaN;
        alpha1_data[jcol].im = 0.0;
      }
      *beta1_size = At.size(0);
      n = At.size(0);
      for (int jcol{0}; jcol < n; jcol++) {
        beta1_data[jcol].re = rtNaN;
        beta1_data[jcol].im = 0.0;
      }
    } else {
      double anrmto;
      double cfrom1;
      double cto1;
      double ctoc;
      double stemp_im_tmp;
      boolean_T guard1{false};
      boolean_T ilascl;
      boolean_T notdone;
      ilascl = false;
      anrmto = anrm;
      guard1 = false;
      if ((anrm > 0.0) && (anrm < 6.7178761075670888E-139)) {
        anrmto = 6.7178761075670888E-139;
        ilascl = true;
        guard1 = true;
      } else if (anrm > 1.4885657073574029E+138) {
        anrmto = 1.4885657073574029E+138;
        ilascl = true;
        guard1 = true;
      }
      if (guard1) {
        absxk = anrm;
        ctoc = anrmto;
        notdone = true;
        while (notdone) {
          cfrom1 = absxk * 2.0041683600089728E-292;
          cto1 = ctoc / 4.9896007738368E+291;
          if ((cfrom1 > ctoc) && (ctoc != 0.0)) {
            stemp_im_tmp = 2.0041683600089728E-292;
            absxk = cfrom1;
          } else if (cto1 > absxk) {
            stemp_im_tmp = 4.9896007738368E+291;
            ctoc = cto1;
          } else {
            stemp_im_tmp = ctoc / absxk;
            notdone = false;
          }
          n = At.size(0) * At.size(1);
          for (int jcol{0}; jcol < n; jcol++) {
            At[jcol].re = stemp_im_tmp * At[jcol].re;
            At[jcol].im = stemp_im_tmp * At[jcol].im;
          }
        }
      }
      xzggbal(At, &ilo, &ihi, rscale_data, &n);
      n = At.size(0);
      if ((At.size(0) > 1) && (ihi >= ilo + 2)) {
        for (int jcol{ilo - 1}; jcol + 1 < ihi - 1; jcol++) {
          int jcolp1;
          jcolp1 = jcol + 2;
          for (int jrow{ihi - 1}; jrow + 1 > jcol + 2; jrow--) {
            xzlartg(At[(jrow + At.size(0) * jcol) - 1],
                    At[jrow + At.size(0) * jcol], &absxk, &s,
                    &At[(jrow + At.size(0) * jcol) - 1]);
            At[jrow + At.size(0) * jcol].re = 0.0;
            At[jrow + At.size(0) * jcol].im = 0.0;
            for (int j{jcolp1}; j <= n; j++) {
              ctoc = At[jrow + At.size(0) * (j - 1)].im;
              cfrom1 = At[jrow + At.size(0) * (j - 1)].re;
              cto1 = At[(jrow + At.size(0) * (j - 1)) - 1].re;
              stemp_im_tmp = At[(jrow + At.size(0) * (j - 1)) - 1].im;
              At[jrow + At.size(0) * (j - 1)].re =
                  absxk * cfrom1 - (s.re * cto1 + s.im * stemp_im_tmp);
              At[jrow + At.size(0) * (j - 1)].im =
                  absxk * At[jrow + At.size(0) * (j - 1)].im -
                  (s.re * stemp_im_tmp - s.im * cto1);
              At[(jrow + At.size(0) * (j - 1)) - 1].re =
                  absxk * cto1 + (s.re * cfrom1 - s.im * ctoc);
              At[(jrow + At.size(0) * (j - 1)) - 1].im =
                  absxk * stemp_im_tmp + (s.re * ctoc + s.im * cfrom1);
            }
            s.re = -s.re;
            s.im = -s.im;
            for (int j{1}; j <= ihi; j++) {
              ctoc = At[(j + At.size(0) * (jrow - 1)) - 1].im;
              cfrom1 = At[(j + At.size(0) * (jrow - 1)) - 1].re;
              cto1 = At[(j + At.size(0) * jrow) - 1].re;
              stemp_im_tmp = At[(j + At.size(0) * jrow) - 1].im;
              At[(j + At.size(0) * (jrow - 1)) - 1].re =
                  absxk * cfrom1 - (s.re * cto1 + s.im * stemp_im_tmp);
              At[(j + At.size(0) * (jrow - 1)) - 1].im =
                  absxk * At[(j + At.size(0) * (jrow - 1)) - 1].im -
                  (s.re * stemp_im_tmp - s.im * cto1);
              At[(j + At.size(0) * jrow) - 1].re =
                  absxk * cto1 + (s.re * cfrom1 - s.im * ctoc);
              At[(j + At.size(0) * jrow) - 1].im =
                  absxk * stemp_im_tmp + (s.re * ctoc + s.im * cfrom1);
            }
          }
        }
      }
      xzhgeqz(At, ilo, ihi, info, alpha1_data, alpha1_size, beta1_data,
              beta1_size);
      if ((*info == 0) && ilascl) {
        notdone = true;
        while (notdone) {
          cfrom1 = anrmto * 2.0041683600089728E-292;
          cto1 = anrm / 4.9896007738368E+291;
          if ((cfrom1 > anrm) && (anrm != 0.0)) {
            stemp_im_tmp = 2.0041683600089728E-292;
            anrmto = cfrom1;
          } else if (cto1 > anrmto) {
            stemp_im_tmp = 4.9896007738368E+291;
            anrm = cto1;
          } else {
            stemp_im_tmp = anrm / anrmto;
            notdone = false;
          }
          for (int jcol{0}; jcol < *alpha1_size; jcol++) {
            alpha1_data[jcol].re *= stemp_im_tmp;
            alpha1_data[jcol].im *= stemp_im_tmp;
          }
        }
      }
    }
  }
}

} // namespace reflapack
} // namespace internal
} // namespace coder

//
// File trailer for xzgeev.cpp
//
// [EOF]
//
