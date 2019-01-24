/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_Sequence
|
|  DESCRIPTION:
|
|  Fill row vector 'v' with a linear sequence of 'cnt' elements from 'start' increment by
|  'step'. If 'cnt' exceeds the number of columns in 'v' only the number of columns available
|  are filled. If columns in 'v' are 0 then fill with 'cnt' and set the column count of 'v'
|  to 'cnt'.
|
|  The values in the sequence are truncated at integer limits if necessary.
|
|  PARAMETERS:    'v'      - vector
|                 'start'  - 1st element in sequence
|                 'step'   - increment; may be negative
|                 'cnt'    - number of elements to fill
|
|  RETURNS:
|
|
|	DATE		AUTHOR		DESCRIPTION OF CHANGE
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

#include "vec.h"

PUBLIC void Vec_Sequence( S_Vec *v, S16 start, S16 step, S16 cnt )
{
   T_VecCols   LVAR n, c;
   S16         LVAR num;
   S32         LVAR l;

   cnt = MAX(cnt, 0);                        /* cnt must be positive                */

   if( v->cols == 0 )                        /* size of 'v' not specified?          */
      { n = cnt; v->cols = cnt; }            /* then it will be 'cnt'               */
   else
      { n = MIN(cnt, v->cols); }             /* else ensure 'cnt' is no larger than size of 'v' */

   for( c = 0, num = start; c < n; c++ )
   {
      v->nums[c] = num;
      l = num + step;
      num = CLIP(l, MIN_S16, MAX_S16);       /* limit next value inside integer */
   }

}

 
