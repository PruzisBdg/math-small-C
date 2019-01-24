/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_Max
|
|  DESCRIPTION:   Returns the highest-valued element in 'v'
|
|  PARAMETERS: - 'v' - the vector
|
|  RETURNS: 
|     
|
|	DATE	      AUTHOR            DESCRIPTION OF CHANGE 
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

#include "vec.h"

PUBLIC S16 Vec_Max( S_Vec const *v )
{
   return v->nums[Vec_MinMax_Idx(v, _Vec_Ctl_GetMax)];
}

// ------------------------------ eof ------------------------------------------------  
