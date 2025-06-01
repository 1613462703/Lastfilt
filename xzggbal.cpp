//
// File: xzggbal.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

// Include Files
#include "xzggbal.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : ::coder::array<creal_T, 2U> &A
//                int *ilo
//                int *ihi
//                int rscale_data[]
//                int *rscale_size
// Return Type  : void
//
namespace coder {
namespace internal {
namespace reflapack {
void xzggbal(::coder::array<creal_T, 2U> &A, int *ilo, int *ihi,
             int rscale_data[], int *rscale_size)
{
  int ii;
  int nzcount;
  *rscale_size = A.size(0);
  ii = A.size(0);
  for (nzcount = 0; nzcount < ii; nzcount++) {
    rscale_data[nzcount] = 1;
  }
  *ilo = 1;
  *ihi = A.size(0);
  if (A.size(0) <= 1) {
    *ihi = 1;
  } else {
    double atmp_im;
    double atmp_re;
    int exitg2;
    int i;
    int j;
    int jj;
    boolean_T exitg3;
    boolean_T exitg4;
    boolean_T found;
    do {
      exitg2 = 0;
      i = 0;
      j = 0;
      found = false;
      ii = *ihi;
      exitg3 = false;
      while ((!exitg3) && (ii > 0)) {
        nzcount = 0;
        i = ii;
        j = *ihi;
        jj = 0;
        exitg4 = false;
        while ((!exitg4) && (jj <= static_cast<unsigned short>(*ihi) - 1)) {
          if ((A[(ii + A.size(0) * jj) - 1].re != 0.0) ||
              (A[(ii + A.size(0) * jj) - 1].im != 0.0) || (ii == jj + 1)) {
            if (nzcount == 0) {
              j = jj + 1;
              nzcount = 1;
              jj++;
            } else {
              nzcount = 2;
              exitg4 = true;
            }
          } else {
            jj++;
          }
        }
        if (nzcount < 2) {
          found = true;
          exitg3 = true;
        } else {
          ii--;
        }
      }
      if (!found) {
        exitg2 = 2;
      } else {
        ii = A.size(0);
        if (i != *ihi) {
          for (jj = 1; jj <= ii; jj++) {
            atmp_re = A[(i + A.size(0) * (jj - 1)) - 1].re;
            atmp_im = A[(i + A.size(0) * (jj - 1)) - 1].im;
            A[(i + A.size(0) * (jj - 1)) - 1] =
                A[(*ihi + A.size(0) * (jj - 1)) - 1];
            A[(*ihi + A.size(0) * (jj - 1)) - 1].re = atmp_re;
            A[(*ihi + A.size(0) * (jj - 1)) - 1].im = atmp_im;
          }
        }
        if (j != *ihi) {
          nzcount = static_cast<unsigned short>(*ihi);
          for (jj = 0; jj < nzcount; jj++) {
            atmp_re = A[jj + A.size(0) * (j - 1)].re;
            atmp_im = A[jj + A.size(0) * (j - 1)].im;
            A[jj + A.size(0) * (j - 1)] = A[jj + A.size(0) * (*ihi - 1)];
            A[jj + A.size(0) * (*ihi - 1)].re = atmp_re;
            A[jj + A.size(0) * (*ihi - 1)].im = atmp_im;
          }
        }
        rscale_data[*ihi - 1] = j;
        (*ihi)--;
        if (*ihi == 1) {
          rscale_data[0] = 1;
          exitg2 = 1;
        }
      }
    } while (exitg2 == 0);
    if (exitg2 != 1) {
      int exitg1;
      do {
        exitg1 = 0;
        i = 0;
        j = 0;
        found = false;
        jj = *ilo;
        exitg3 = false;
        while ((!exitg3) && (jj <= *ihi)) {
          nzcount = 0;
          i = *ihi;
          j = jj;
          ii = *ilo;
          exitg4 = false;
          while ((!exitg4) && (ii <= *ihi)) {
            if ((A[(ii + A.size(0) * (jj - 1)) - 1].re != 0.0) ||
                (A[(ii + A.size(0) * (jj - 1)) - 1].im != 0.0) || (ii == jj)) {
              if (nzcount == 0) {
                i = ii;
                nzcount = 1;
                ii++;
              } else {
                nzcount = 2;
                exitg4 = true;
              }
            } else {
              ii++;
            }
          }
          if (nzcount < 2) {
            found = true;
            exitg3 = true;
          } else {
            jj++;
          }
        }
        if (!found) {
          exitg1 = 1;
        } else {
          ii = A.size(0);
          if (i != *ilo) {
            for (jj = *ilo; jj <= ii; jj++) {
              atmp_re = A[(i + A.size(0) * (jj - 1)) - 1].re;
              atmp_im = A[(i + A.size(0) * (jj - 1)) - 1].im;
              A[(i + A.size(0) * (jj - 1)) - 1] =
                  A[(*ilo + A.size(0) * (jj - 1)) - 1];
              A[(*ilo + A.size(0) * (jj - 1)) - 1].re = atmp_re;
              A[(*ilo + A.size(0) * (jj - 1)) - 1].im = atmp_im;
            }
          }
          if (j != *ilo) {
            nzcount = static_cast<unsigned short>(*ihi);
            for (jj = 0; jj < nzcount; jj++) {
              atmp_re = A[jj + A.size(0) * (j - 1)].re;
              atmp_im = A[jj + A.size(0) * (j - 1)].im;
              A[jj + A.size(0) * (j - 1)] = A[jj + A.size(0) * (*ilo - 1)];
              A[jj + A.size(0) * (*ilo - 1)].re = atmp_re;
              A[jj + A.size(0) * (*ilo - 1)].im = atmp_im;
            }
          }
          rscale_data[*ilo - 1] = j;
          (*ilo)++;
          if (*ilo == *ihi) {
            rscale_data[*ilo - 1] = *ilo;
            exitg1 = 1;
          }
        }
      } while (exitg1 == 0);
    }
  }
}

} // namespace reflapack
} // namespace internal
} // namespace coder

//
// File trailer for xzggbal.cpp
//
// [EOF]
//
