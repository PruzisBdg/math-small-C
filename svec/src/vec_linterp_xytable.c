/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_Linterp_XYTable
|
|  DESCRIPTION:
|
|  Linear interpolation of 'x' on x-y table contained in vector 't'. If x is outside the
|  table then returns y at the nearest bound.
|
|  The x-axis can be ascending or descending. It x-coords don't have to be evenly spaced
|  but they must be monotonic.
|
|  PARAMETERS:    - 't'       vector of paired x,y to interpolate against. x values should be
|                             row 0; y values in row 1. The length of the vector is t->cols
|                             t->rows should be set to 2.
|
|                 - 'x'       is input
|
|  RETURNS:       'y' result of interpolation
|
|	DATE		   AUTHOR             DESCRIPTION OF CHANGE 
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

#include "vec.h"

PUBLIC S16 Vec_Linterp_XYTable( S_Vec const *t, S16 x ) 
{
   T_VecCols   LVAR c, size;
   S16       * LVAR p; 
   S16         LVAR x0, x1, y0, y1;
   BOOL        LVAR rampsUp;

   size = t->cols;

   /* x-axis increasing or decreasing */
   if( t->nums[0] < t->nums[size-1] ) rampsUp = TRUE; else rampsUp = FALSE;

   /* Search forward through the table (ascending/descending'x') until find an x-coord which
      is greater/less than the input 'x'.
   */
   for( c = 0, p = t->nums; c < size-1; c++, p++ ) 
   {
      if( (rampsUp && (*p > x)) || (!rampsUp && (*p < x)) ) break;
   }

   /* If the x-coord was at or outside table limits, return the 'y' at the same end */

   if(  c == 0 ||                             /* 'x' below bottom        */
        ( c >= size-1 && 
          ((rampsUp && (x >= *p)) || (!rampsUp && (x <= *p)))
        ) 
     )
   {
      return *(p+size);                      /* then return end coord   */
   }
   else 
   {
      x1 = *p; y1 = *(p+size);               /* upper x, y              */
      p--; 
      x0 = *p; y0 = *(p+size);               /* lower x, y              */

      /* Interpolate from x to y */
      return y0 + (((y1 - y0) * (S32)(x - x0)) / (x1 - x0));
   }
}



 
