//
// File: xdhseqr.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

// Include Files
#include "xdhseqr.h"
#include "lastfilt_rtwutil.h"
#include "rt_nonfinite.h"
#include "xdlanv2.h"
#include "xnrm2.h"
#include "xrot.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &h
// Return Type  : int
//
namespace coder {
namespace internal {
namespace reflapack {
int eml_dlahqr(::coder::array<double, 2U> &h)
{
  double aa;
  double ab;
  double ba;
  double bb;
  double d;
  double rt1r;
  double rt2r;
  double s;
  double tst;
  int info;
  int ldh;
  int n;
  n = h.size(0);
  ldh = h.size(0);
  info = 0;
  if ((n != 0) && (n != 1)) {
    double v[3];
    double SMLNUM;
    int i;
    int itmax;
    int kdefl;
    boolean_T exitg1;
    v[0] = 0.0;
    v[1] = 0.0;
    v[2] = 0.0;
    for (int j{0}; j <= n - 4; j++) {
      h[(j + h.size(0) * j) + 2] = 0.0;
      h[(j + h.size(0) * j) + 3] = 0.0;
    }
    if (n - 2 >= 1) {
      h[(n + h.size(0) * (n - 3)) - 1] = 0.0;
    }
    if (n <= 10) {
      itmax = 10;
    } else {
      itmax = n;
    }
    itmax *= 30;
    kdefl = 0;
    SMLNUM = 2.2250738585072014E-308 *
             (static_cast<double>(n) / 2.2204460492503131E-16);
    i = n - 1;
    exitg1 = false;
    while ((!exitg1) && (i + 1 >= 1)) {
      int L;
      int hoffset;
      int its;
      boolean_T exitg2;
      boolean_T goto150;
      L = 1;
      goto150 = false;
      its = 0;
      exitg2 = false;
      while ((!exitg2) && (its <= itmax)) {
        int k;
        boolean_T exitg3;
        k = i;
        exitg3 = false;
        while ((!exitg3) && (k + 1 > L)) {
          ba = std::abs(h[k + h.size(0) * (k - 1)]);
          if (ba <= SMLNUM) {
            exitg3 = true;
          } else {
            bb = std::abs(h[k + h.size(0) * k]);
            tst = std::abs(h[(k + h.size(0) * (k - 1)) - 1]) + bb;
            if (tst == 0.0) {
              if (k - 1 >= 1) {
                tst = std::abs(h[(k + h.size(0) * (k - 2)) - 1]);
              }
              if (k + 2 <= n) {
                tst += std::abs(h[(k + h.size(0) * k) + 1]);
              }
            }
            if (ba <= 2.2204460492503131E-16 * tst) {
              tst = std::abs(h[(k + h.size(0) * k) - 1]);
              if (ba > tst) {
                ab = ba;
                ba = tst;
              } else {
                ab = tst;
              }
              tst = std::abs(h[(k + h.size(0) * (k - 1)) - 1] -
                             h[k + h.size(0) * k]);
              if (bb > tst) {
                aa = bb;
                bb = tst;
              } else {
                aa = tst;
              }
              s = aa + ab;
              if (ba * (ab / s) <=
                  std::fmax(SMLNUM, 2.2204460492503131E-16 * (bb * (aa / s)))) {
                exitg3 = true;
              } else {
                k--;
              }
            } else {
              k--;
            }
          }
        }
        L = k + 1;
        if (k + 1 > 1) {
          h[k + h.size(0) * (k - 1)] = 0.0;
        }
        if (k + 1 >= i) {
          goto150 = true;
          exitg2 = true;
        } else {
          int m;
          kdefl++;
          if (kdefl - kdefl / 20 * 20 == 0) {
            s = std::abs(h[i + h.size(0) * (i - 1)]) +
                std::abs(h[(i + h.size(0) * (i - 2)) - 1]);
            tst = 0.75 * s + h[i + h.size(0) * i];
            aa = -0.4375 * s;
            ab = s;
            bb = tst;
          } else if (kdefl - kdefl / 10 * 10 == 0) {
            s = std::abs(h[(k + h.size(0) * k) + 1]) +
                std::abs(h[(k + h.size(0) * (k + 1)) + 2]);
            tst = 0.75 * s + h[k + h.size(0) * k];
            aa = -0.4375 * s;
            ab = s;
            bb = tst;
          } else {
            tst = h[(i + h.size(0) * (i - 1)) - 1];
            ab = h[i + h.size(0) * (i - 1)];
            aa = h[(i + h.size(0) * i) - 1];
            bb = h[i + h.size(0) * i];
          }
          s = ((std::abs(tst) + std::abs(aa)) + std::abs(ab)) + std::abs(bb);
          if (s == 0.0) {
            rt1r = 0.0;
            ab = 0.0;
            rt2r = 0.0;
            aa = 0.0;
          } else {
            tst /= s;
            ab /= s;
            aa /= s;
            bb /= s;
            ba = (tst + bb) / 2.0;
            tst = (tst - ba) * (bb - ba) - aa * ab;
            ab = std::sqrt(std::abs(tst));
            if (tst >= 0.0) {
              rt1r = ba * s;
              rt2r = rt1r;
              ab *= s;
              aa = -ab;
            } else {
              rt1r = ba + ab;
              rt2r = ba - ab;
              if (std::abs(rt1r - bb) <= std::abs(rt2r - bb)) {
                rt1r *= s;
                rt2r = rt1r;
              } else {
                rt2r *= s;
                rt1r = rt2r;
              }
              ab = 0.0;
              aa = 0.0;
            }
          }
          m = i - 1;
          exitg3 = false;
          while ((!exitg3) && (m >= k + 1)) {
            tst = h[m + h.size(0) * (m - 1)];
            ba = h[(m + h.size(0) * (m - 1)) - 1];
            bb = ba - rt2r;
            s = (std::abs(bb) + std::abs(aa)) + std::abs(tst);
            tst /= s;
            v[0] = (tst * h[(m + h.size(0) * m) - 1] + (ba - rt1r) * (bb / s)) -
                   ab * (aa / s);
            v[1] = tst * (((ba + h[m + h.size(0) * m]) - rt1r) - rt2r);
            v[2] = tst * h[(m + h.size(0) * m) + 1];
            s = (std::abs(v[0]) + std::abs(v[1])) + std::abs(v[2]);
            v[0] /= s;
            v[1] /= s;
            v[2] /= s;
            if ((m == k + 1) ||
                (std::abs(h[(m + h.size(0) * (m - 2)) - 1]) *
                     (std::abs(v[1]) + std::abs(v[2])) <=
                 2.2204460492503131E-16 * std::abs(v[0]) *
                     ((std::abs(h[(m + h.size(0) * (m - 2)) - 2]) +
                       std::abs(ba)) +
                      std::abs(h[m + h.size(0) * m])))) {
              exitg3 = true;
            } else {
              m--;
            }
          }
          for (int b_k{m}; b_k <= i; b_k++) {
            int nr;
            hoffset = (i - b_k) + 2;
            if (hoffset >= 3) {
              nr = 3;
            } else {
              nr = hoffset;
            }
            if (b_k > m) {
              hoffset = (b_k + ldh * (b_k - 2)) - 1;
              for (int j{0}; j < nr; j++) {
                v[j] = h[j + hoffset];
              }
            }
            ab = v[0];
            rt2r = 0.0;
            if (nr > 0) {
              tst = blas::xnrm2(nr - 1, v);
              if (tst != 0.0) {
                aa = rt_hypotd_snf(v[0], tst);
                if (v[0] >= 0.0) {
                  aa = -aa;
                }
                if (std::abs(aa) < 1.0020841800044864E-292) {
                  hoffset = 0;
                  do {
                    hoffset++;
                    for (int j{2}; j <= nr; j++) {
                      v[j - 1] *= 9.9792015476736E+291;
                    }
                    aa *= 9.9792015476736E+291;
                    ab *= 9.9792015476736E+291;
                  } while ((std::abs(aa) < 1.0020841800044864E-292) &&
                           (hoffset < 20));
                  aa = rt_hypotd_snf(ab, blas::xnrm2(nr - 1, v));
                  if (ab >= 0.0) {
                    aa = -aa;
                  }
                  rt2r = (aa - ab) / aa;
                  tst = 1.0 / (ab - aa);
                  for (int j{2}; j <= nr; j++) {
                    v[j - 1] *= tst;
                  }
                  for (int j{0}; j < hoffset; j++) {
                    aa *= 1.0020841800044864E-292;
                  }
                  ab = aa;
                } else {
                  rt2r = (aa - v[0]) / aa;
                  tst = 1.0 / (v[0] - aa);
                  for (int j{2}; j <= nr; j++) {
                    v[j - 1] *= tst;
                  }
                  ab = aa;
                }
              }
            }
            v[0] = ab;
            if (b_k > m) {
              h[(b_k + h.size(0) * (b_k - 2)) - 1] = ab;
              h[b_k + h.size(0) * (b_k - 2)] = 0.0;
              if (b_k < i) {
                h[(b_k + h.size(0) * (b_k - 2)) + 1] = 0.0;
              }
            } else if (m > k + 1) {
              h[(b_k + h.size(0) * (b_k - 2)) - 1] =
                  h[(b_k + h.size(0) * (b_k - 2)) - 1] * (1.0 - rt2r);
            }
            rt1r = v[1];
            tst = rt2r * v[1];
            if (nr == 3) {
              s = v[2];
              aa = rt2r * v[2];
              for (int j{b_k}; j <= n; j++) {
                d = h[(b_k + h.size(0) * (j - 1)) - 1];
                ba = h[b_k + h.size(0) * (j - 1)];
                bb = h[(b_k + h.size(0) * (j - 1)) + 1];
                ab = (d + rt1r * ba) + s * bb;
                d -= ab * rt2r;
                h[(b_k + h.size(0) * (j - 1)) - 1] = d;
                ba -= ab * tst;
                h[b_k + h.size(0) * (j - 1)] = ba;
                bb -= ab * aa;
                h[(b_k + h.size(0) * (j - 1)) + 1] = bb;
              }
              if (b_k + 3 <= i + 1) {
                hoffset = b_k + 2;
              } else {
                hoffset = i;
              }
              for (int j{0}; j <= hoffset; j++) {
                d = h[j + h.size(0) * (b_k - 1)];
                ba = h[j + h.size(0) * b_k];
                bb = h[j + h.size(0) * (b_k + 1)];
                ab = (d + rt1r * ba) + s * bb;
                d -= ab * rt2r;
                h[j + h.size(0) * (b_k - 1)] = d;
                ba -= ab * tst;
                h[j + h.size(0) * b_k] = ba;
                bb -= ab * aa;
                h[j + h.size(0) * (b_k + 1)] = bb;
              }
            } else if (nr == 2) {
              for (int j{b_k}; j <= n; j++) {
                s = h[(b_k + h.size(0) * (j - 1)) - 1];
                d = h[b_k + h.size(0) * (j - 1)];
                ab = s + rt1r * d;
                s -= ab * rt2r;
                h[(b_k + h.size(0) * (j - 1)) - 1] = s;
                d -= ab * tst;
                h[b_k + h.size(0) * (j - 1)] = d;
              }
              for (int j{0}; j <= i; j++) {
                s = h[j + h.size(0) * (b_k - 1)];
                d = h[j + h.size(0) * b_k];
                ab = s + rt1r * d;
                s -= ab * rt2r;
                h[j + h.size(0) * (b_k - 1)] = s;
                d -= ab * tst;
                h[j + h.size(0) * b_k] = d;
              }
            }
          }
          its++;
        }
      }
      if (!goto150) {
        info = i + 1;
        exitg1 = true;
      } else {
        if ((L != i + 1) && (L == i)) {
          rt1r = h[(i + h.size(0) * i) - 1];
          s = h[i + h.size(0) * (i - 1)];
          d = h[i + h.size(0) * i];
          xdlanv2(&h[(i + h.size(0) * (i - 1)) - 1], &rt1r, &s, &d, &tst, &ab,
                  &aa, &ba, &bb, &rt2r);
          h[(i + h.size(0) * i) - 1] = rt1r;
          h[i + h.size(0) * (i - 1)] = s;
          h[i + h.size(0) * i] = d;
          if (n > i + 1) {
            hoffset = i + (i + 1) * ldh;
            blas::xrot((n - i) - 1, h, hoffset, ldh, hoffset + 1, ldh, bb,
                       rt2r);
          }
          blas::xrot(i - 1, h, (i - 1) * ldh + 1, i * ldh + 1, bb, rt2r);
        }
        kdefl = 0;
        i = L - 2;
      }
    }
  }
  return info;
}

} // namespace reflapack
} // namespace internal
} // namespace coder

//
// File trailer for xdhseqr.cpp
//
// [EOF]
//
