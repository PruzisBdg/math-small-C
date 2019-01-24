/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_Mean
|
|  DESCRIPTION:
|
|  Return mean of the elements in the 1st/only row of 'v'.
|
|  PARAMETERS:    'v'   - vector
|
|  RETURNS:       mean of 1st row of 'v'
|     
|
|	DATE        AUTHOR            DESCRIPTION OF CHANGE 
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

#include "vec.h"

PUBLIC S16 Vec_Mean( S_Vec const *v )
{
   return (S16)( Vec_SumRow(v) / (S16)v->cols);    /* **** promote v->vols to signed or get division errors **** */
}


 
