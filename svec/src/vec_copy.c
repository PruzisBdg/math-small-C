/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_Copy
|
|  DESCRIPTION:
|
|     Copy vector 'src' onto 'dest'. Row/column resolution given by Vec_ByElement().
|
|  PARAMETERS: - 'vec'  vector
|              - 'ctl'  control byte selects min or max
|
|  RETURNS:
|     
|
|	DATE        AUTHOR            DESCRIPTION OF CHANGE 
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

#include "vec.h"

PRIVATE void copy( S16 *a, S16 *b, S16 parm) { *a = *b; }

PUBLIC void Vec_Copy( S_Vec *dest, S_Vec const *src ) 
{
   Vec_ByElement(dest, src, copy, 0);
}

// --------------------------------------- eof ---------------------------------------------- 
