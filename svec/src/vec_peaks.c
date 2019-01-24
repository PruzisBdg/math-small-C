/*---------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_Peaks
|
|  Finds any/all of minima, maxima and zero-crossings in 'in'; returns results in 'out'.
| 
|  'in' may be a 1-row or multi-row vector. If 1-row then the Vec_Peaks() returns the 
|  column indices of the extrema. If multi-row then the 2nd row (row 1) is assumed to by 'y'
|  and is scanned for peaks. The function then extracts the corresponding 'x' values
|  from row 0.
|
|  What information is returned in 'out' depends what is requested via the 'ctl' flags,
|  whats supplied in 'in' and how many rows are available in 'out'. For each min/max found 
|  _Peaks() assembles all the information BOTH REQUESTED AND AVAILABLE to a fixed priority 
|  in a column vector. It then truncates that vector to the row size of 'out' and appends
|  it to 'out'
|
|     'in'         flags                   out vector
|     rows  '_Indices'  '_XVals'   (before truncation into 'out')
|     ------------------------------------------------------------
|      1        1          x         indices  / y-values / peak-type
|      x        0          0         y-values / peak-type
|      x        1          0         indices  / y-values / peak-type
|      >1       0          0         y-values / peak-type
|      >1       1          0         indices  / y-values / peak-type
|      >1       0          1         x-values / y-values / peak-type
|      >1       1          1         indices  / x-values / y-values / peak-type
|     
|
|  If there are more columns in 'out' than min/maxs found then all min/maxs are included
|  in 'out'. Otherwise 'out' is completely filled with mins/maxs with the largest absolute
|  values. So e.g if you want just the 3 largest peaks then pre-size 'out' to 3 columns.
|
|  PARAMETERS:  'out'    - holds minima, maxima, zero-crossing
|               'in'       - source vector
|               'ctl'      - control flags
|
|     control flags are:
|
|        _Vec_Peaks_Maxs      - get maxima
|        _Vec_Peaks_Mins      - get minima
|        _Vec_Peaks_Zeros     - get zero-crossings
|        _Vec_Peaks_Rank      - if max or mins then ranks from largest absolute amplitude down
|        _Vec_Peaks_Indices   - output indices of maxs,mins,zeros
|        _Vec_Peaks_XValues   - output x-values of peaks (if available - input vector must be multi-row)
|
|  Returns the total number of mins/maxes found
|
|	DATE		   AUTHOR            DESCRIPTION OF CHANGE
|	--------		-------------		-------------------------------------
|
----------------------------------------------------------------------------------------------*/

#include "vec.h"

PUBLIC S16 Vec_Peaks( S_Vec *out, S_Vec const *in, U8 ctl ) 
{
   T_VecRows LVAR yRow,       /* row containg y-values; either the only row in 'in' (0) or row 1 */
                  r;
             
   T_VecCols LVAR c, d, 
                  maxToRecord;
             
   S16       LVAR n0, n1, n2,
                  xVal,
                  nOut, 
                  exCnt; 
                  
   S16            b1[3];
   
   U8        LVAR exType, gotX;
   S_Vec     v1;

   /* Too few rows or cols then quit now */
   if( in->cols < 3 || in->rows < 1 ) return 0;

   /* Scan 1st or 2nd row */
   if( in->rows == 1 ) yRow = 0; else yRow = 1;

   /* Note the space available in the results vector. Then zero it. We will
      refill it up to the space available.
   */
   maxToRecord = out->cols;
   out->cols = 0;

   /* Count extrema */
   for( c = 1, exCnt = 0; c < in->cols-1; c++ )       /* scan the vector */
   {
      /* Get three points which have different value, the centre of which is the current index
         into 'in'. If a min or max is sharp then these will be 3 consecutive points on the
         vector. However at a shallow peak the vector may have several values in a row identical
         So can't always pick 3 consective points         
      */
      n1 = Vec_Read1(in, yRow, c);              /* Get the midpoint (of three)            */

      d = c-1;                                  /* Starting one back from midpoint        */
      do
      {
         n0 = Vec_Read1(in, yRow, d);           /* Look back...                           */
         if(d) d--;
      }
      while( n0 == n1 && d > 0 );               /* until different value from midpoint    */
                                                /* OR start of vector                     */

      d = c+1;                                  /* Starting one forward from midpoint     */
      do
      {
         n2 = Vec_Read1(in, yRow, d);           /* Look forward...                        */
         d++;
      }
      while( n2 == n1 && d < (in->cols - 1) );  /* until different value from midpoint    */
                                                /* OR end of vector                       */

      /* With the above rules a flat peak will be counted multiple times, once for
         each equal value. To avoid this skip to the last equal value. Since 'd' points
         to the 1st unequal value above the equal values AND 'd' is post incremented, the
         last equal values is at 'd' - 2
      */
      c = d - 2;

      /* Classify 3 points as min, max, zero-cross or none of the previous */

      exType = _Vec_Peaks_exType_None;                                  /* unless set below  */

      if( BSET(ctl, _Vec_Peaks_Maxs) && (n1 > n0) && (n1 > n2) )        /* local max?        */
      {
         exType = _Vec_Peaks_exType_Max;
      }
      else if( BSET(ctl, _Vec_Peaks_Mins) && (n1 < n0) && (n1 < n2) )   /* local min?        */
      { 
         exType = _Vec_Peaks_exType_Min;
      }
      else if( BSET(ctl, _Vec_Peaks_Zeros) )
      { 
         if( ((n1 > n0) && (n2 > n1)) )                        /* zero-cross up?                      */
            { exType = _Vec_Peaks_exType_ZeroUp; }
         else if( ((n1 < n0) && (n2 < n1)) )                   /* zero-cross down?                    */
            { exType = _Vec_Peaks_exType_ZeroDown; }
      }
      if( exType != _Vec_Peaks_exType_None )                   /* got an extremum?                    */
      {
         exCnt++;                                              /* then count it                       */

         if( exCnt > maxToRecord )                             /* output vector full?                 */
         {
                                                               /* then don't add to it, just count.   */
         }
         else                                                  /* else add to output vector           */
         {
            if( in->rows == 1) 
               { gotX = FALSE; }
            else
               { gotX = TRUE; xVal = Vec_Read1(in, 0, c); }

            if( out->rows == 1 )                               /* one output row? to be filled with   */
            {                                                  /* either indices or x-values          */
               if( !gotX ||                                    /* one SOURCE row? OR                  */
                   BSET(ctl, _Vec_Peaks_Indices) )             /* caller requested indices?           */
                  { nOut = c; }                                /* then fill with index                */
               else 
                  { nOut = xVal; }                             /* else fill with x-value              */

               Vec_Write1( out, nOut, 0, exCnt-1 );            /* insert index or xVal                */
               out->cols = exCnt;                              /* and update count                    */
            }
            else                                               /* else multiple rows - fill by priority */
            {
               _Vec_Make(&v1, b1, 4, 1);                       /* column vector to hold result        */

               if( BSET(ctl, _Vec_Peaks_Indices ) )            /* want indices?                       */
               { 
                  Vec_Write1(&v1,  c, 0, 0);                   /* then 1st row is index               */
                  r = 1;                                       /* and row 1 will be filled next       */
               }
               else
                  { r = 0; }                                   /* else 1st row unfilled               */

               if( BSET(ctl, _Vec_Peaks_XValues) && gotX )     /* want X-values AND have them?        */
               {
                  Vec_Write1(&v1, xVal, r, 0);                 /* then add to next open row           */
                  r++;
               }
               Vec_Write1(&v1, n1, r, 0);                      /* Add peak value to next row          */
               r++;
               Vec_Write1(&v1, exType, r, 0);                  /* Add peak type to final row          */
               v1.rows = out->rows;                            /* Trim vector to rows available in output vector */

               Vec_Join(out, (S_Vec const *)&v1, 0, out->cols);/* and append to current output vector */
            }
         }
      }
   }
   return exCnt;
}


 
