/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_ByFraction
|
|  DESCRIPTION:
|
|     For the 1st / only row in 'dest'
|
|        dest[n] = num * src[n] / den
|
|  The result on each element is limited to  MIN_INT < dest[n] < MAX_INT.
|
|  If 'src' and 'dest' don't have the same number of cols then then number of cols operated
|  on is the lower of dest->cols and src->cols. If either is zero the the count (zero) is
|  ignored and the other is taken as the number of elements to process.
|
|  If the denominator is large then the floating-point version is faster on an 8051.
|  Timings for a 5-element vector on 22MHz C8051 are:
|              fixed = 900usec;  float = 400usec
|
|  PARAMETERS:  'dest'  - results vector (can be the same as 'src'
|               'src'   - source vector
|               'num'   - numerator
|               'den'   - denominator
|
|  RETURNS: 
|     
|
|	DATE	      AUTHOR            DESCRIPTION OF CHANGE 
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

#include "vec.h"

#ifndef _HAS_FLOAT
   #error "_HAS_FLOAT not defined"
#else

#if _HAS_FLOAT == 0

PUBLIC void Vec_ByFraction( S_Vec *dest, S_Vec const *src, S16 num, S16 den )
{
   T_VecCols LVAR cols;
   T_VecCols LVAR c;
   S32       LVAR l;

   if( src->cols == 0 )                         /* no 'src' cols specified    */
      { cols = dest->cols; }                    /* so use 'dest' cols         */
   else if( dest->cols == 0 )                   /* etc..                      */
      { cols = src->cols; }
   else                                         /* else both specified        */
      { cols = MIN(src->cols, dest->cols); }    /* so use lower               */

   for( c = 0; c < cols; c++ )
   {
      l = num * (S32)src->nums[c]; 
      l = l/den;
      dest->nums[c] = CLIP(l, MIN_INT, MAX_INT);            /* clip if overflow  */
   }
}

#elif _HAS_FLOAT == 1


PUBLIC void Vec_ByFraction( S_Vec *dest, S_Vec const *src, S16 num, S16 den )
{
   T_VecCols LVAR cols;
   T_VecCols LVAR c;
   float     LVAR f1, f2;

   if( src->cols == 0 )                         /* no 'src' cols specified    */
      { cols = dest->cols; }                    /* so use 'dest' cols         */
   else if( dest->cols == 0 )                   /* etc..                      */
      { cols = src->cols; }
   else                                         /* else both specified        */
      { cols = MIN(src->cols, dest->cols); }    /* so use lower               */
      
   f1 = (float)num/(float)den;                  /* Get quotient. N.B cast to float BEFORE dividing */     

   for( c = 0; c < cols; c++ )                  /* for each element           */
   {
      f2 = f1 * (float)src->nums[c]; 
      dest->nums[c] = (S16)CLIP(f2, MIN_S16, MAX_S16);   /* clip if overflow  */
   }
}

#endif
#endif

// -------------------------------- eof ---------------------------------------

 
