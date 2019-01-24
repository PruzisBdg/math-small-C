/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_Join
|
|  Insert 'src' into 'dest' at 'startRow', 'destRow', overwriting the exisitng values in 'dest'.
|  Some, all, or none of 'src' may fit inside the original 'dest'. The resulting vector (in 'dest')
|  is expanded if necessary. This contrasts with Vec_Write() where 'src' is clipped to fit inside
|  'dest'.
|
|  DESCRIPTION:
|
|
|  PARAMETERS:    'dest'      - resulting combined vector
|                 'src'       - vector to fold into 'dest'
|                 'startRow'  - row / col offset for insertion
|                 'startCol'  -
|
|  RETURNS:    - vector index to min / max
|     
|
|	DATE		AUTHOR		DESCRIPTION OF CHANGE
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

#include "vec.h"

PRIVATE void revCopy( S16 *dest, S16 const *src, S16 cnt )
{
   /* Copy 'src' to 'dest' but in reverse order. */
   for( src += (cnt-1), dest += (cnt-1); cnt; cnt--, src--, dest-- ) *dest = *src;
}


PUBLIC void Vec_Join( S_Vec *dest, S_Vec const *src, T_VecRows startRow, T_VecCols startCol )
{

   T_VecRows   LVAR r, i;
   T_VecCols   LVAR c;
   T_RowByCol  LVAR rc0, rc1;
   S16         * LVAR s, * LVAR d;

   r = MAX(dest->rows, startRow + src->rows);            /* rows and cols in combined vector          */
   c = MAX(dest->cols, startCol + src->cols);

   rc1 = r * c;                                          /* num elements in final vector              */
   rc0 = dest->rows * dest->cols;                        /* elements in original vector               */

   if( rc1 > rc0 )                                       /* combined vector larger than original?     */
   {
      FillInts( dest->nums + rc0, 0, (rc1 - rc0) );      /* then first zero-fill new buffer elements (from 'rc0' to 'rc1') */
   }

   if( c > dest->cols )                                  /* more cols so existing rows in buffer must be spaced out?    */
   {
      for( i = dest->rows; i; i-- )                      /* for each row - outermost-first so don't overwrite           */
      {
         s = dest->nums + ((i-1) * dest->cols);          /* copy-from: rows were spaced 'dest->cols' in buffer          */
         d = dest->nums + ((i-1) * c);                   /* copy-to: rows now spaced 'c' in buffer                      */
         revCopy( d, (S16 const *)s, dest->cols );       /* Shift row (in reverse order so won't overwrite if dest overlaps source) */
         FillInts( s, 0, d-s );                          /* zero-fill vacated elements (beween 's' and 'd')             */
      }
   }

   for( i = 0; i < src->rows; i++ )                      /* for each row in 'src'      */
   {
      revCopy(
         dest->nums + ((c * (i + startRow)) + startCol), /* copy into expanded 'dest'  */
         (S16 const *)(src->nums + (src->cols * i)),     /* 'src' row in its buffer    */
         src->cols );                                    /* 'src' rows this long       */
   }
   
   /* done copying, update 'dest' size */
   dest->rows = r;
   dest->cols = c;
}

// --------------------------------------- eof --------------------------------------------
