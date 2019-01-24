/*---------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_Extents
|
|  Derive the extents 'e' of individual row vectors in 'v'. May scan successive vectors
|  for global min/max.
|
|  PARAMETERS:  'v'    - vector to be scanned
|               'e'    - vector 2 columns, each row is min/max of corresponding row in 'v'.
|               'ctl'  - control flags
|                          - '_Accumulate' => get global extents of 'e', 'v'; to scan
|                              multiple vectors for global min/max
|
|  RETURNS:
|
|	DATE		   AUTHOR            DESCRIPTION OF CHANGE
|	--------		-------------		-------------------------------------
|
----------------------------------------------------------------------------------------------*/

#include "vec.h"

PUBLIC void Vec_Extents( S_Vec *e, S_Vec const *v, U8 ctl )
{
   T_VecRows c, d;
   S_Vec     v2;
   S16       min, max;

   if( BSET(ctl, _Vec_Extents_AddColIdx) )         /* row 0 of 'e' is min/max col indices of 'v'?  */
   {
      e->rows = v->rows + 1;                       /* 'e' rows <- 'v' rows + one for indices       */
      Vec_Write1(e, 0, 0, 0);                      /* e(0,0) <- 0                                  */
      Vec_Write1(e, v->cols, 0, 1);                /* e(0,1) <- num cols in 'v'                    */
   }
   else
   {
      e->rows = v->rows;                           /* A row in 'e' for each row in 'v'    */
   }

   e->cols = 2;                                    /* min and max                         */

   for( c = 0; c < e->rows; c++ )                  /* for each row                        */
   {
      Vec_RefRow(&v2, v, c);                       /* access the row                      */
      min = _Vec_Min((S_Vec const *)&v2);          /* Get min/max                         */
      max = _Vec_Max((S_Vec const *)&v2);

      if( BSET(ctl, _Vec_Extents_Accumulate ) )    /* global min/max of 'e', 'v'?         */
      {
         min = MIN(min, Vec_Read1((S_Vec const *)e, c, 0));    /* then get global min/max */
         max = MAX(max, Vec_Read1((S_Vec const *)e, c, 1));
      }                                            /* else min/max of 'v' alone           */

      /* If indices are in row 0 then write extents for row 'c' of 'v' to row 'c' + 1 of
         'e'; else its the same row.
      */
      if( BSET(ctl, _Vec_Extents_AddColIdx) ) { d = c + 1; } else { d = c; }

      Vec_Write1(e, min, d, 0);                    /* e[c, 0] <- min                      */
      Vec_Write1(e, max, d, 1);                    /* e[c, 1] <- max                      */
   }
}

// ----------------------------------- eof ---------------------------------------



 
