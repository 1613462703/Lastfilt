//
// File: lastfilt.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

// Include Files
#include "lastfilt.h"
#include "butter.h"
#include "filter.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// 根据filterType选择滤波器
//
// Arguments    : const double x[50001]
//                double fs
//                double fc_low
//                double fc_high
//                double N
//                const char filterType_data[]
//                const int filterType_size[2]
//                double y[50001]
// Return Type  : void
//
void lastfilt(const double x[], double fs, double fc_low, double fc_high,
              double N, const char filterType_data[],
              const int filterType_size, double y[])
{
  static const char cv2[8]{'b', 'a', 'n', 'd', 'p', 'a', 's', 's'};
  static const char cv3[8]{'b', 'a', 'n', 'd', 's', 't', 'o', 'p'};
  static const char cv1[4]{'h', 'i', 'g', 'h'};
  static const char cv[3]{'l', 'o', 'w'};
  double b_data[2003];
  double a_data[1003];
  int exitg1;
  int kstr;
  boolean_T b_bool;
  b_bool = false;
  if (filterType_size == 3) {
    kstr = 0;
    do {
      exitg1 = 0;
      if (kstr < 3) {
        if (filterType_data[kstr] != cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  if (b_bool) {
    kstr = 0;
  } else {
    b_bool = false;
    if (filterType_size == 4) {
      kstr = 0;
      do {
        exitg1 = 0;
        if (kstr < 4) {
          if (filterType_data[kstr] != cv1[kstr]) {
            exitg1 = 1;
          } else {
            kstr++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
    if (b_bool) {
      kstr = 1;
    } else {
      b_bool = false;
      if (filterType_size == 8) {
        kstr = 0;
        do {
          exitg1 = 0;
          if (kstr < 8) {
            if (filterType_data[kstr] != cv2[kstr]) {
              exitg1 = 1;
            } else {
              kstr++;
            }
          } else {
            b_bool = true;
            exitg1 = 1;
          }
        } while (exitg1 == 0);
      }
      if (b_bool) {
        kstr = 2;
      } else {
        b_bool = false;
        if (filterType_size == 8) {
          kstr = 0;
          do {
            exitg1 = 0;
            if (kstr < 8) {
              if (filterType_data[kstr] != cv3[kstr]) {
                exitg1 = 1;
              } else {
                kstr++;
              }
            } else {
              b_bool = true;
              exitg1 = 1;
            }
          } while (exitg1 == 0);
        }
        if (b_bool) {
          kstr = 3;
        } else {
          kstr = -1;
        }
      }
    }
  }
  switch (kstr) {
  case 0: {
    int a_size[2];
    int b_size[2];
    //  低通滤波器函数
    coder::butter(N, fc_low / (fs / 2.0), b_data, b_size, a_data, a_size);
    coder::filter(b_data, b_size, a_data, a_size, x, y);
  } break;
  case 1: {
    int a_size[2];
    int b_size[2];
    //  高通滤波器函数
    coder::b_butter(N, fc_high / (fs / 2.0), b_data, b_size, a_data, a_size);
    coder::filter(b_data, b_size, a_data, a_size, x, y);
  } break;
  case 2: {
    double b_fc_low[2];
    int a_size[2];
    int b_size[2];
    //  带通滤波器函数
    b_fc_low[0] = fc_low / (fs / 2.0);
    b_fc_low[1] = fc_high / (fs / 2.0);
    coder::butter(N, b_fc_low, b_data, b_size, a_data, a_size);
    coder::filter(b_data, b_size, a_data, a_size, x, y);
  } break;
  case 3: {
    double b_fc_low[2];
    int a_size[2];
    int b_size[2];
    //  带阻滤波器函数
    b_fc_low[0] = fc_low / (fs / 2.0);
    b_fc_low[1] = fc_high / (fs / 2.0);
    coder::b_butter(N, b_fc_low, b_data, b_size, a_data, a_size);
    coder::filter(b_data, b_size, a_data, a_size, x, y);
  } break;
  }
}

//
// File trailer for lastfilt.cpp
//
// [EOF]
//
