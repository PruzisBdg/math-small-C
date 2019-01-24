/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_MeanAbs
|
|  DESCRIPTION:
|
|  Return mean of the absolute value of elements in the 1st/only row of 'v'.
|
|  PARAMETERS:    'v'   - vector
|
|  RETURNS:       mean absolute of 1st row of 'v'
|     
|
|	DATE        AUTHOR            DESCRIPTION OF CHANGE 
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

#include "vec.h"

PUBLIC S16 Vec_MeanAbs( S_Vec const *v )
{
   T_VecCols LVAR c;
   S16       LVAR n;
   S32       LVAR sum;

   for( c = 0, sum = 0; c < v->cols; c++ )
   {
      n = v->nums[c];
      sum += ABS(n);
   }
   return (S16)(sum / (S16)v->cols);    /* **** promote v->vols to signed or get division errors **** */
}


 
