/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_Span
|
|  DESCRIPTION:   Returns the difference between the largest and smallest elemnts in 'v'
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
#include "arith.h"

PUBLIC S16 Vec_Span( S_Vec const *v )
{
   return ClipLongToInt(Vec_Max(v) - Vec_Min(v));
   
}

// ------------------------------ eof ------------------------------------------------  
