/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_Fill
|
|  DESCRIPTION:
|
|  PARAMETERS: - 'vec'  vector
|              - 'n'    fill value
|
|  RETURNS: 
|     
|
|	DATE		AUTHOR		DESCRIPTION OF CHANGE 
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

#include "vec.h"

PUBLIC void Vec_Fill( S_Vec *vec, S16 n ) 
{
   U16   LVAR c;
   S16 * LVAR d;

   for( c = vec->cols * vec->rows, d = vec->nums; c; c-- ) *d++ = n;  
}

// ------------------------------------ eof -------------------------------------------------- 
