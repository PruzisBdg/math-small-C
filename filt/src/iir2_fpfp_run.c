/*-------------------------------------------------------------------------------------------------
|
|  IIRFF2_Run
|
|  Runs 2nd-order IIR 'f' on 'in'. Returns result. 
|
|  A 2nd order IIR, canonical form (Direct 2) has a 2-element buffer. 
|  (2 poles, 2 zeros) 'tapIdx' indexes the buffer; it is 0 or !0.
|
|  Order of coffs in S_IIRF2.coffs is:
|
|  D1, D2, N0, N1, N2   (D = demonimator, N = numerator)
|
|  A0 always equals (1 << _CoffFSBits) so doesn't have to be in the coffs list
|
|  PARAMETERS:    - 'f'    the filter
|                 - 'in'   input value
|
|  RETURNS:       - the filtered result
|     
-----------------------------------------------------------------------------------------*/

#include "iirfilt_fp.h"

#define LPROD(a,b)  ((a) * (b))

PUBLIC float IIRFF2_Run( S_IIRF2  *f, float in ) 
{
   T_IIRFAcc   z1, z2,     /* temp storage for buffer data  */
               m;          /* m = den(in)  */

   T_IIRFAcc   *p;

   T_IIRFCoffs CONST *cp;  /* to read filter coffs          */
   U8          tapIdx;     /* either the 1st or 2nd tap     */

   /* Get buffer contents into z1, z2. z1 has the youngest sample.  */
   p = f->buf;

   if( f->tapIdx )
      { z1 = *(p++); z2 = *p; }
   else
      { z2 = *(p++); z1 = *p; }

   /* Denominator: m = (A0 * in) + (A1 * z1) + (A2 + z2)  */
   cp = f->coffs;

   /* Denominator: m = (A0 * in) + (A1 * z1) + (A2 + z2)  */
   m = (T_IIRFAcc)in + LPROD(*cp,  z1) + LPROD(*(cp+1),  z2);

   /* Update buffer, replacing the oldest sample  */
   tapIdx = f->tapIdx;
   if( tapIdx ) { *(f->buf+1) = m; } else { *f->buf = m; }

   /* Flip tap idx 1 <-> 0  */
   f->tapIdx = tapIdx ^ 0x01;
 
   /* Numerator: y = (B0 * m) + (B1 * z1) + (B2 * z2)  */
   return LPROD(*(cp+2),  m ) + LPROD(*(cp+3),  z1) + LPROD(*(cp+4),  z2);
}

// ---------------------------- eof -------------------------------------- 
