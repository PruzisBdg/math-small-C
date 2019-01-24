/* -------------------------------------------------------------------------
|
|  Floating point IIR Filter - Multiple 2nd order sections - parallel
|
|  Pruzina 8/9/04
|
|  This is the IIR_ package with floating point accumulators and coefficients
|  in place of 16bit coffs and 32bit accumulators. In an IIR filter when the
|  transistion frequency is small compared to the sample rate the coffs are
|  small and the accumulator values large. The coffs are therefore not precise
|  and the 32 bit accumulators can overrange. This version of the IIR filter avoids
|  these issues at the expense of speed
|
|  Set T_IIRFAcc to float or double depending on the precision required.
|
|  Public functions:
|
|	   single 2nd order IIR, canonical (direct II)
|
|	      IIRF2_Init()		- initialise coffs etc
|	      IIRF2_Run()		- run, return result
|  
|	   2xn order IIR, multiple 2nd-order, parallel
|
|	      IIRFNx2_Init()
|	      IIRFNx2_Run()
|
----------------------------------------------------------------------------- */

#include "iirfilt_fp.h"
#include "arith.h"


/* Macro allows bounds-checking, inline assembly or target-dependent func()  */
#define LPROD(a,b)  ((a) * (b))


/* ======================= Single 2nd order Section ============================= */


/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  IIRF2_Run
|
|  DESCRIPTION:
|
|     Runs 2nd-order IIR 'f' on 'in'. Returns result. 
|
|     A 2nd order IIR, canonical form (Direct 2) has a 2-element buffer. 
|     (2 poles, 2 zeros) 'tapIdx' indexes the buffer; it is 0 or !0.
|
|     Order of coffs in S_IIRF2.coffs is:
|
|        -B1, -B2, A0, A1, A2   (B = demonimator, A = numerator)
|
|     B0 always equals 1 so doesn't have to be in the coffs list
|
|  N.B. In the arithemtic below, (B1 * z1), (B2 * z2) are ADDED to the denominator
|  sum, instead of being subtracted as defined in DIRECT FORM 2. This speeds the
|  fixed-point code and, for compatibility with this, we keep this convention here
|  in the floating point code. However now B1, B2 MUST BE SIGN-REVERSED IN THE 
|  COEFFICIENT TABLE.
|
|
|  PARAMETERS:    - 'f'    the filter
|                 - 'in'   input value
|
|  RETURNS:       - the filtered result
|     
|
|	DATE		AUTHOR		DESCRIPTION OF CHANGE
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/


PUBLIC S16 IIRF2_Run( S_IIRF2  *f, S16 in ) 
{
   T_IIRFAcc   z1, z2,     /* temp storage for buffer data  */
               m;          /* m = den(in)                   */

   T_IIRFAcc   *p;

   T_IIRFCoffs CONST *cp;  /* to read filter coffs          */
   U8          tapIdx;     /* either the 1st or 2nd tap     */

   /* Get buffer contents into z1, z2. z1 has the youngest sample.  */
   p = f->buf;

   if( f->tapIdx )
      { z1 = *(p++); z2 = *p; }
   else
      { z2 = *(p++); z1 = *p; }

   cp = f->coffs;

   /* Denominator: m = (B0 * in) - (B1 * z1) - (B2 + z2)  */
   m = (T_IIRFAcc)in + LPROD(*cp,  z1) + LPROD(*(cp+1),  z2);

   /* Update buffer, replacing the oldest sample  */
   tapIdx = f->tapIdx;
   if( tapIdx ) { *(f->buf+1) = m; } else { *f->buf = m; }

   /* Flip tap idx 1 <-> 0  */
   f->tapIdx = tapIdx ^ 0x01;
 
   /* Numerator: y = (A0 * m) + (A1 * z1) + (A2 * z2)  */
   return ClipFloatToInt(LPROD(*(cp+2),  m ) + LPROD(*(cp+3),  z1) + LPROD(*(cp+4),  z2));
}




/* ========================== end: IIR Filters ======================================= */
