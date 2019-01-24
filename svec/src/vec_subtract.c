/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_Subtract
|
|  DESCRIPTION:   'dest' = 'dest' - 'src'. Row/column resolation given by Vec_ByElement().
|
|  PARAMETERS: - 'dest'  'src' vectors
|
|  RETURNS:
|
|	DATE	      AUTHOR            DESCRIPTION OF CHANGE
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

#include "vec.h"

PRIVATE void subtract( S16 *a, S16 *b, S16 parm) { *a = *a - *b; }

PUBLIC void Vec_Subtract( S_Vec *dest, S_Vec const *src )
{
   Vec_ByElement(dest, src, subtract, 0);
}

// ----------------------------------- eof -------------------------------------------- 
