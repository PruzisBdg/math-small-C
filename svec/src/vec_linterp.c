/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_Linterp
|
|  Linear interpolation of vector 'in' onto 'axis'; result in 'out'.
|
|  The number of points interpolated is the lower of the number of columns specified in
|  'out' and 'axis'. If the column count in one of these is zero then it is not used to 
|  reckon the number of interpolations. At least one of the 2 vectors must have a column 
|  count, else there will be no interpolation. 
|
|  DESCRIPTION:
|
|  PARAMETERS:    'in'     -  2-row input vector. row 0 are x values.
|                 'out'    -  1-row vector is 'in', interpolated
|                 'axis'   -  axis of interpolation
|
|  RETURNS:
|
|	DATE		   AUTHOR             DESCRIPTION OF CHANGE 
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

#include "vec.h"

PUBLIC void Vec_Linterp(S_Vec *out, S_Vec const *in, S_Vec const *axis )
{
   T_VecCols LVAR c, cnt;

   cnt = 0;                               /* until assign interpolation cnt below */

   if( axis->cols )
      { cnt = axis->cols; }

   if( out->cols )
      { cnt = MIN(cnt, out->cols); }      /* is the min of non-zero column counts for 'axis', 'out' */

   for( c = 0; c < cnt; c++ )
   {
      out->nums[c] = Vec_Linterp_XYTable(in, axis->nums[c]);
   }
   out->rows = 1;
   out->cols = cnt;
}



 
