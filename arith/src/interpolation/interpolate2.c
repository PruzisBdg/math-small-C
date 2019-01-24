/* ------------------------- Interpolate2 ----------------------------------

   Interpolation along a set of points which are at fixed intervals. Since the interval 
   is fixed, only the y values are supplied. The interpolation table can be up to 128
   points.

   Inputs:
         tbl      - y values of the function to be interpolated (which are assumed to be
                    at fixed intervals). 

         x        - index(x) to 'tbl'. x is scaled such that 2^8 (256) equals 1 table 
                    interval. The index goes from 0 upwards. 'x' is a int and its
                    range limits the number of points in the interpolation table to
                    2^15 / 2^8 = 128 entries.

         tblPoints  - must be >= 3.

   Returns:
         y interpolated from x. If x lies outside the table limits it is clipped
         to table limits before interpolation. If 'tblPoints' is < 3 returns 0.

   
   Interpolation is by divided differences along y0 -> y01 -> y012

               y0 -_
                    - y01 -_               y01 = y1-y0   y12 = y2-y1
               y1           - y012         
                      y12                  y012 = y12 - y01 / 2
               y2

   Interpolation is along the forward path y0 -> y01 -> y012 giving:

               y = y0 + (x-x0)*y01 + (x-x0)*(x-x1)*y012

   Without internal roundoff errors, any interpolation path will give the same result.

   The interpolation limits gracefully if x is outpside the limits for the table. The
   difference between successive table entries should not exceed 2^15 - 1 (32767) otherwise 
   numeric overflow will occur.
*/
#include "common.h"
#include "arith.h"

/* ------------------------------------------------------------------------------
|
|  getTblIdx()
|
|  Given 'x' ordinate, return index into table from which to interpolate.
|
-------------------------------------------------------------------------------- */

PRIVATE S16 getTblIdx(S16 x, U8 tblPoints)
{
   /* Now reckon table entries to use. Normally these will be tbl[n], tbl[n+1], tbl[n+2]
      but, if 'n' is towards either end of the table, the entries can't run outside 
      tbl[0] or tbl[tblPoints]
   */
   if( (x >> 8) >= tblPoints - 2) {    /* at top ? */
      return tblPoints - 3;            /* use tbl[size-2], [size-1], [size] */
      }
   else if( x < 0 ) {                  /* at bottom? */
      return 0;                        /* use tbl[0],[1],[2] */
      }
   else {
      return x >> 8;                   /* Get integer part of x */
      }
}


PUBLIC S16 Interpolate2( S16 CONST *tbl, S16 x, U8 tblPoints ) {

   S16 CONST *yp;    // 'y' table pointer
   S16       dx;     // fractional part of x

   if( tblPoints < 3 )                                // Table too small?
   {
      return tbl[0];                                  // then just return the 1st element
   }

   x = ClipInt(x, 0, ((S16)(tblPoints - 1) << 8) );   // Clip 'x' to the limits of the table
   yp = tbl + getTblIdx(x, tblPoints);                // Pointer to triad of 'y's to interpolate from

   /* Get (x - x0). x ranges from x0 - x2; hence (x - x0) will range from 0 to 2 * 2^8 (512). */
   dx = x - (getTblIdx(x, tblPoints) << 8);

   /* Do interpolation.
     
      (x - x1) = x - x0 - 1_integer_part = dx - 256 
   */
   return 
   ClipLongToInt
   (
      *yp + 
      ( MulS16(dx, *(yp+1) - *yp) >> 8) + 
      (
         (
            MulS16(dx, dx - 256) * 
            (S32)((*(yp+2) -2*(*(yp+1))+ *yp) >> 1)
         ) >> 16
      )
   );
}


// --------------------------------------- eof -------------------------------------------
 
