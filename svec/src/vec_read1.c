/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_Read1
|
|  DESCRIPTION:
|
|     Read element at 'row', 'col'
|
|  PARAMETERS:    'v'            the vector
|                 'row', 'col'   element to read. If -1 then reads the last row/col
|
|  RETURNS:       value of the element; 0 if 'row' 'col' is outside the range of the vector
|     
|
|	DATE        AUTHOR            DESCRIPTION OF CHANGE 
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

#include "vec.h"

PUBLIC S16 Vec_Read1( S_Vec const *v, T_VecRows row, T_VecCols col )
{
   if( row == _Vec_LAST_ROW) row = v->rows - 1;   /* '-1 or Max' then set to last element */
   if( col == _Vec_LAST_COL) col = v->cols - 1;   /* N.B T_VecRows, T_VecCols may be unsigned so use == not '< 0' */

   row = MIN(row, v->rows - 1);                 /* limit to within vector */
   col = MIN(col, v->cols - 1);
   
   return v->nums[(v->cols * (T_RowByCol)row) + col];
}

// ------------------------------------- eof -----------------------------------------------
