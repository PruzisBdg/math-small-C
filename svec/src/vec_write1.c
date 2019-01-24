/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_Write1
|
|  DESCRIPTION:
|
|     Write element at 'row', 'col'
|
|  PARAMETERS:    'v'            the vector
|                 'row', 'col'   element to write. If -1 then write the last row/col
|
|  RETURNS:
|
|
|	DATE        AUTHOR            DESCRIPTION OF CHANGE
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

#include "vec.h"

PUBLIC void Vec_Write1( S_Vec *v, S16 n, T_VecRows row, T_VecCols col )
{
   if( row == Vec_MaxRows) row = v->rows - 1;   /* '-1 or Max' then set to last element */
   if( col == Vec_MaxCols) col = v->cols - 1;   /* N.B T_VecRows, T_VecCols may be unsigned so use == not '< 0' */

   row = MIN(row, v->rows - 1);                 /* limit to within vector */
   col = MIN(col, v->cols - 1);

   v->nums[(v->cols * (T_RowByCol)row) + col] = n;
}

// ------------------------------------------ eof ---------------------------------------------
