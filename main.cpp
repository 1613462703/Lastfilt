//
// File: main.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Feb-2025 17:30:20
//

/*************************************************************************/
/* This automatically generated example C++ main file shows how to call  */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

// Include Files
#include "main.h"
#include "lastfilt.h"
#include "lastfilt_terminate.h"
#include "rt_nonfinite.h"

// Function Declarations
static void argInit_1x50001_real_T(double result[50001]);

static void argInit_1xd8_char_T(char result_data[], int result_size[2]);

static char argInit_char_T();

static double argInit_real_T();

// Function Definitions
//
// Arguments    : double result[50001]
// Return Type  : void
//
static void argInit_1x50001_real_T(double result[50001])
{
  // Loop over the array to initialize each element.
  for (int idx1{0}; idx1 < 50001; idx1++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx1] = argInit_real_T();
  }
}

//
// Arguments    : char result_data[]
//                int result_size[2]
// Return Type  : void
//
static void argInit_1xd8_char_T(char result_data[], int result_size[2])
{
  // Set the size of the array.
  // Change this size to the value that the application requires.
  result_size[0] = 1;
  result_size[1] = 2;
  // Loop over the array to initialize each element.
  for (int idx1{0}; idx1 < 2; idx1++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result_data[idx1] = argInit_char_T();
  }
}

//
// Arguments    : void
// Return Type  : char
//
static char argInit_char_T()
{
  return '?';
}

//
// Arguments    : void
// Return Type  : double
//
static double argInit_real_T()
{
  return 0.0;
}

//
// Arguments    : int argc
//                char **argv
// Return Type  : int
//
int main(int, char **)
{
  // The initialize function is being called automatically from your entry-point
  // function. So, a call to initialize is not included here. Invoke the
  // entry-point functions.
  // You can call entry-point functions multiple times.
  main_lastfilt();
  // Terminate the application.
  // You do not need to do this more than one time.
  lastfilt_terminate();
  return 0;
}

//
// Arguments    : void
// Return Type  : void
//
void main_lastfilt()
{
  static double dv[50001];
  static double y[50001];
  double fs_tmp;
  int filterType_size[2];
  char filterType_data[8];
  // Initialize function 'lastfilt' input arguments.
  // Initialize function input argument 'x'.
  fs_tmp = argInit_real_T();
  // Initialize function input argument 'filterType'.
  argInit_1xd8_char_T(filterType_data, filterType_size);
  // Call the entry-point 'lastfilt'.
  argInit_1x50001_real_T(dv);
  lastfilt(dv, fs_tmp, fs_tmp, fs_tmp, fs_tmp, filterType_data, filterType_size,
           y);
}

//
// File trailer for main.cpp
//
// [EOF]
//
