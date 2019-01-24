/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_RefRow
|
|  DESCRIPTION:
|
|  Setup vector 'sub' to access row 'row' of reference vector 'ref'. The data in 'ref' is 
|  not duplicated.
|
|  PARAMETERS: 
|
|     'ref' -  reference vector
|     'sub' -  a vector accessing row 'row' of 'ref'
|     'row' -  row number of 'ref' to be accessed
|
|  RETURNS: 
|
|
|	DATE		AUTHOR		DESCRIPTION OF CHANGE 
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

#include "vec.h"

PUBLIC void Vec_RefRow( S_Vec *sub, S_Vec const *ref, T_VecRows row )
{
   T_VecRows LVAR r;

   sub->rows = 1;                                  /* Accessing 1 row                  */
   sub->cols = ref->cols;                          /* the whole vector wide            */
   r = ref->rows - 1;
   r = MIN(row, r);                                /* Limit row access to inside 'ref' */
   sub->nums = ref->nums + ((U16)ref->cols * r);   /* Jump in correct data position    */
}

// ------------------------------------ eof -----------------------------------------------------
