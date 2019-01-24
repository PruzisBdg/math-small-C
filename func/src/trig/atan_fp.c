#include "bldcfg.h"
#include "common.h"
#include "mathfunc.h"
#include <math.h>

typedef float T_Trig;

/* Prototype for arctangent function using continued
 * fractions.  This is Listing 6.7 of text.
 */


 /* Rational approximation for atan(x)
  * This polynomial uses a minimaxed 5th-order
  * ratio of polynomials.  Input angles are restricted
  * to values no greater than 15 degrees.  Accuracy is
  * better than 4e-8 over the full range of inputs.
  */
PUBLIC T_Trig ArctanFP(T_Trig x){

  // constants for segmentation
  #define b 	0.523598775598		// pi/6
  #define k 	0.577350269       // tan(pi/6)
  #define b0 	0.261799387			// pi/12
  #define k0   0.267949192			// tan(pi/12)

  // constants for rational polynomial
  #define A 	0.999999020228907
  #define B 	0.257977658811405
  #define C 	0.59120450521312
  
  T_Trig 	ang;
  T_Trig 	x2;
  BIT 		comp = FALSE;
  BIT 		hi_seg = FALSE;
  BIT       sign;

  // make argument positive
  sign = (x < 0);
  x = fabs(x);

  // limit argument to 0..1
  if(x > 1){
    comp = TRUE;
    x = 1/x;
  }

  // determine segmentation
  if(x > k0){
    hi_seg = TRUE;
    x = (x - k)/(1 + k*x);
  }

  /* argument is now < tan(15 degrees)
   * approximate the function
   */
  x2 = x * x;
  ang = x*(A + B*x2)/(1 + C*x2);

  // now restore offset if needed
  if(hi_seg)
    ang += b;

  // restore complement if needed
  if(comp)
    ang = HALFPI - ang;

  // restore sign if needed
  return sign ? -ang : ang;
}

 
