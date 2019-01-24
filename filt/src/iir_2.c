/* -------------------------------------------------------------------------
|
|  Integer IIR Filter - Multiple 2nd order sections - parallel
|
|  Pruzina 6/3/03
|
|	Gain of 2nd-order IIRs is >>14 i.e they will have a gain of 1 when
|	used with 14bit coffs. 14bit coffs give reasonable accuracy up to 8th
|	order and allow considerable headroom with 12-14 bit data.
|
|	Public functions:
|
|		single 2nd order IIR, canonical (direct II)
|
|		iir2_Init()		- initialise coffs etc
|		iir2_Run()		- run, return result
|
|		2xn order IIR, multiple 2nd-order, parallel
|
|		iirNx2_Init()
|		iirNx2P_Run()
|
----------------------------------------------------------------------------- */

#include "iirfilt.h"
#include "arith.h"

#define _L(n)  ((S32)(n))
#define _S(n)  ((S16)(n))

/* Macro allows bounds-checking, inline assembly or target-dependent func()  */
#define LPROD(a,b)  (_L(a) * _L(b))




/* ======================= Single 2nd order Section ============================= */


/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  IIR2_Init
|
|  DESCRIPTION:
|
|     Make / initialise 2nd-order section 'f' with coffs 'coffs'. The filter buffer is zeroed
|
|  PARAMETERS:    - 'f'       the filter
|                 - 'coffs'   the coffs
|
|  RETURNS:
|     
|
|	DATE		AUTHOR		DESCRIPTION OF CHANGE 
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

PUBLIC void iir2_Init( iir2_S _IIR_Mem *f, S16 CONST *coffs, U8 coffsScalePwr2 ) 
{
	f->buf[0] = 0;
	f->buf[1] = 0;
   f->coffs  = coffs;
   f->tapIdx = 0;
   f->coffsPwr2 = coffsScalePwr2;
}


/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  IIR2_Run
|
|  DESCRIPTION:
|
|     Runs 2nd-order IIR 'f' on 'in'. Returns result. 
|
|     A 2nd order IIR, canonical form (Direct 2) has a 2-element buffer. 
|     (2 poles, 2 zeros) 'tapIdx' indexes the buffer; it is 0 or !0.
|
|     Order of coffs in S_IIR2.coffs is:
|
|        -B1, -B2, A0, A1, A2   (B = demonimator, A = numerator)
|
|     B0 always equals (1 << _CoffFSBits) so doesn't have to be in the coffs list
|
|   
|  N.B. In the arithemtic below, (B1 * z1), (B2 * z2) are ADDED to the denominator
|  sum, instead of being subtracted as defined in DIRECT FORM 2. This speeds the
|  fixed-point code, However now B1, B2 MUST BE SIGN-REVERSED IN THE COEFFICIENT TABLE.
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

// This formulation faster and more compact for 8051 and other MCUs with
// small register sets.
#if _TOOL_IS == TOOL_RIDE_8051

PUBLIC S16 iir2_Run( iir2_S _IIR_Mem *f, S16 in ) 
{
   S32           z1, z2,       /* temp storage for buffer data   */
                 m;       /* m = den(in)  */
                
   S16     CONST * cp;
   U8      coffsRS;

   coffsRS = f->coffsPwr2;    // Cache this to compact and speed.

   /* Get accumulator values; scale down before applying to MAC (below)  */
   z1 = f->buf[f->tapIdx ? 0 : 1] >> coffsRS;
   z2 = f->buf[f->tapIdx ? 1 : 0] >> coffsRS;

   cp = f->coffs;             // Cache this

   /* Denominator: m = (B0 * in) + (B1 * z1) + (B2 + z2)  */
   m = AplusBS32( AplusBS32(MulS16(*(cp+1),  z2), MulS16(*cp,  z1)), _L(in) << coffsRS );

   /* Update buffer, replacing the oldest sample  */
   if( f->tapIdx ) { *(f->buf+1) = m; } else { *f->buf = m; }

   /* Flip tap idx 1 <-> 0  */
   f->tapIdx = f->tapIdx ^ 0x01;
 
   /* Numerator: y = (A0 * m) + (A1 * z1) + (A2 * z2)  */
   return ClipS32toS16( (AplusBS32(MulS16(*(cp+4),  z2), AplusBS32(MulS16(*(cp+3),  z1), MulS16(*(cp+2),  (m >> coffsRS) )))) >> coffsRS);
}

// else, for 16/32bit register-bank MCU's 
#else

PUBLIC S16 iir2_Run( iir2_S _IIR_Mem *f, S16 in ) 
{
   S32           z1, z2,       /* temp storage for buffer data   */
                 m;       /* m = den(in)  */
                
   S32  _IIR_Mem *p;

   S16     CONST * cp;
   U8        tapIdx;

   /* Get buffer contents into z1, z2. z1 has the youngest sample.  */
   p = f->buf;

   if( f->tapIdx ) 
      { z1 = *(p++); z2 = *p; }
   else 
      { z2 = *(p++); z1 = *p; }

   /* Scale down before applying to MAC (below)  */
   z1 = z1 >> f->coffsPwr2;
   z2 = z2 >> f->coffsPwr2;

   /* Denominator: m = (B0 * in) + (B1 * z1) + (B2 + z2)  */
   cp = f->coffs;
   m = LPROD(*(cp+1),  z2) + LPROD(*cp,  z1) + (_L(in) << f->coffsPwr2);     /* Coff A0 is always x1.   */

   /* Update buffer, replacing the oldest sample  */
   tapIdx = f->tapIdx;
   if( tapIdx ) { *(f->buf+1) = m; } else { *f->buf = m; }

   /* Flip tap idx 1 <-> 0  */
   f->tapIdx = (tapIdx + 1) % 2;
 
   /* Numerator: y = (A0 * m) + (A1 * z1) + (A2 * z2)  */
   return (LPROD(*(cp+4),  z2) + LPROD(*(cp+3),  z1) + LPROD(*(cp+2),  (m >> f->coffsPwr2) )) >> f->coffsPwr2;
}
#endif // _TOOL_IS == TOOL_RIDE_8051

/* ----------------------------- eof -------------------------------------- */
