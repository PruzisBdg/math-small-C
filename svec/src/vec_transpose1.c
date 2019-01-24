/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_Transpose1
|
|  Transpose 'v' in place
|
-------------------------------------------------------------------------------------------------*/

#include "vec.h"

PUBLIC void Vec_Transpose1( S_Vec *v )
{
   T_RowByCol i, j;
   S16 n;
   T_VecRows  r;
   T_VecCols  c;

   if( v->rows > 1 || v->cols > 1 )                      // more than one row or col?
   {                                                     // then must reorder contents
      for( r = 0; r < v->rows; r++ )
      {
         for( c = 0; c < v->cols; c++ )                  // for each element
         {                                               // Exchange v[r,c] <-> v[c,r]
            i = v->nums[(v->cols * (T_RowByCol)r) + c];  // index for one end of the swap
            j = v->nums[(v->rows * (T_RowByCol)c) + r];  // to get other index exchange row, col roles

            n = v->nums[i];                              // and do the swap
            v->nums[i] = v->nums[j];
            v->nums[j] = n;
         }
      }
   }
   j = v->rows; v->rows = v->cols; v->cols = j;          // Finally, swap the row and column counts
}

// ------------------------------------ eof -----------------------------------------------------

