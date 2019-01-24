/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_AddScalar
|
|  DESCRIPTION:
|
|  'dest' = 'src' + 'n' (scalar).   Row/column resolution given by Vec_ByElement().
|
|  PARAMETERS: -  'src', 'dest'  - vectors
|                 'n'            - to be added to 'src'
|
|  RETURNS:
|
|	DATE	      AUTHOR            DESCRIPTION OF CHANGE
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

#include "vec.h"

PRIVATE void addScalar( S16 *a, S16 *b, S16 parm) { *a = *b + parm; }

PUBLIC void Vec_AddScalar( S_Vec *dest, S_Vec const *src, S16 n )
{
   Vec_ByElement(dest, src, addScalar, n);
}

// ------------------------------------ eof ------------------------------------------------ 
