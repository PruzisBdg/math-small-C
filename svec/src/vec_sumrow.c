/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_SumRow
|
|  DESCRIPTION:
|
|  Return sum of the elements in the 1st/only row of 'v'.
|
|  PARAMETERS:    'v'   - vector to be summed
|
|  RETURNS:       sum of 1st row of 'v'
|     
|
|	DATE        AUTHOR            DESCRIPTION OF CHANGE 
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

#include "vec.h"

PUBLIC S32 Vec_SumRow( S_Vec const *v )
{
   T_VecCols LVAR c;
   S32       LVAR sum;

   for( c = 0, sum = 0; c < v->cols; c++ )
      { sum += v->nums[c]; }

   return sum;
}



 
