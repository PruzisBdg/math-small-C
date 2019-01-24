/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_Write
|
|  Write 'src' onto 'dest' at 'startRow', 'destRow', overwriting the exisitng values in 'dest'.
|  If any part of 'src' lies outside 'dest' that part is clipped. This contrasts with Vec_Join()
|  where 'dest' may be expanded to fit 'src'.
|
|
|  PARAMETERS:    'dest'      - resulting combined vector
|                 'src'       - vector to fold into 'dest'
|                 'startRow'  - row / col offset for insertion
|                 'startCol'  -
|
|  RETURNS:
|
-------------------------------------------------------------------------------------------------*/

#include "vec.h"

PUBLIC void Vec_Write( S_Vec *dest, S_Vec const *src, T_VecRows startRow, T_VecCols startCol )
{
   T_VecRows r, rowCopy;
   T_VecCols c, colCopy;

   if( startRow >= dest->rows || startCol >= dest->cols )   // insert point is outside 'dest'
   {
      return;                                               // then do nothing
   }
   else
   {
      // Copy as many rows and cols as in 'src' but no more than will fit in 'dest'
      rowCopy = MIN((dest->rows - startRow), src->rows);
      colCopy = MIN((dest->cols - startCol), src->cols);

      for(r = 0; r < rowCopy; r++)           // for each row
      {
         for(c = 0; c < colCopy; c++)        // for each col in a row
         {                                   // copy one value
            Vec_Write1(dest, _Vec_Read1(src, r, c), r+startRow, c+startCol);
         }
      }
   }
}

// -------------------------------------- eof ----------------------------------------------------
