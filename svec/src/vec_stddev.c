/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_StdDev
|
|  DESCRIPTION:
|
|  Returns sample standard deviation of the elements in the 1st/only row of 'v'.
|  The summation is guarded against overflow; if overflow occurs the result will
|  always be low.
|
|  PARAMETERS:    'v'   - vector
|
|  RETURNS:       standard deviation of 1st row of 'v'; 0 if 'v' has less than
|                 2 columns.
|
|	DATE        AUTHOR            DESCRIPTION OF CHANGE 
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

#include "vec.h"

PUBLIC S16 Vec_StdDev( S_Vec const *v )
{
   T_VecCols   LVAR c;
   S16         LVAR mean, d;
   S32         LVAR l, sum;

   /* Avoid overflow when calculating (x - mean) by /2 */
   mean = Vec_Mean(v) >> 1;

   for( c = 0, sum = 0; c < v->cols; c++ )
   {
      d = (v->nums[c] >> 1) - mean;             /* error /2                */
      l = d * (S32)d;                           /* error^2 / 4             */

      if( (sum + l) < sum )                     /* numeric overflow?       */
         { sum = MAX_S32; }                     /* then limit to max       */
      else
         { sum += l; }                          /* else add to total       */
   }
   if( v->cols < 2 )
      { return 0; }
   else
      /* Return sample deviation (N-1); *2 because /2 earlier */
      { return 2 * SqrtLong( sum / (S16)(v->cols - 1) ); }
}


 
