/*---------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_RMS
|
|  Return the root mean square of the 1st row of 'v'.
|  If 'v' is empty returns 0. If there was overrange returns -1.
|
|  RMS calculations on long vectors can overrange the accumulator. When this occurs
|  the Vec_RMS() scales down the vector and retries the calculation until it
|  proceeds without overflow.
|
|  PARAMETERS:  'v'  - the vector
|
|  RETURNS:     rms of 'v'
|
|	DATE		   AUTHOR            DESCRIPTION OF CHANGE
|	--------		-------------		-------------------------------------
|
----------------------------------------------------------------------------------------------*/

#include "vec.h"

/* ----------------------------- getRMSDiv -----------------------------------

   Returns rms of v/div; -1 if there was overrange
*/

PRIVATE S16 getRMSDiv( S_Vec const *v, S16 div )
{
   T_VecCols   LVAR c;
   S16         LVAR d;
   S32         LVAR l, sum;

   for( c = 0, sum = 0; c < v->cols; c++ )      /* for each vector element    */
   {
      d = v->nums[c];
      l = (d * (S32)d) / (div * div);           /* l <- (v[c]/div)^2          */

      if( (sum + l) < sum )                     /* numeric overflow?          */
         { return -1; }                         /* then quit with error flag  */
      else
         { sum += l; }                          /* else add to total          */
   }
   return SqrtLong( sum / (S16)v->cols );       /* return rms                 */
}

PUBLIC S16 Vec_RMS( S_Vec const *v )
{
   S16 r, div;

   if( v->cols == 0 )                           /* 'v' empty?                 */
      { return 0; }                             /* then return 0              */
   else
   {
      for( div = 1; div <= 256; div *= 2 )      /* for div = 1,2,4... 256                    */
      {
         if( (r = getRMSDiv( v, div )) > 0 )    /* Get rms of v/div                          */
            { return r; }                       /* no overrange, return rms                  */
      }                                         /* else overrange, double 'div', try again   */
      return -1;
   }
}



 
