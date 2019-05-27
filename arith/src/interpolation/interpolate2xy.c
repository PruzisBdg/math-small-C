/* --------------------------------- Interpolate2XY -----------------------------------------------

   Interpolation along a set of x,y coordinates which do not have to be at fixed intervals.
   The interpolation table can be up to 128 points.

   Inputs:
         tbl      - x,y values of the function to be interpolated.
                    x coordinates must be ASCENDING order.

         x        - x coordinate to be interpolated.

         tblPoints  - number of table entries; must be >= 3.

   Returns:
         y interpolated from x. If x lies outside the table limits it is clipped
         to table limits before interpolation. If 'tblPoints' is < 3 returns 0.


   Interpolation by divided differences along y0 -> y01 -> y012

               x0    y0 -_                       y01 = y1-y0 / x1-x0
                          - y01 -_               y12 = y2-y1 / x2-x1
               x1    y1           - y012
                            y12                  y012 = y12-y01 / x2-x0
               x2    y2

   Interpolation is along the forward path y0 -> y01 -> y012 giving:

               y = y0 + (x-x0)*y01 + (x-x0)*(x-x1)*y012

   Without internal roundoff errors, any interpolation path will give the same result.

   The interpolation limits gracefully if x is outpside the limits for the table. The
   difference between successive table entries should not exceed 2^15 - 1 (32767) otherwise
   numeric overflow will occur.

   Pruzina
*/
#include "common.h"
#include "arith.h"

#define Interp2_XShift 8
#define _L(n) ((S32)(n))

#if _TARGET_IS == TARGET_LIB_LARGE || _TARGET_IS == TARGET_LIB_RIDE_THUMB2 || _TARGET_IS == _TARGET_LIB_ARM

PUBLIC S16 Interpolate2XY( S_XY CONST * tbl, S16 x, U8 tblPoints ) {

   S_XY CONST * NEAR p, * NEAR q;            /* to scan the table */

   S16 NEAR   y0, y1, y2, /* table entries        */
               x0, x1, x2,
               x01, x12,
               y01, y12,   /* y2-y1 and y1-y0      */
               y012;       /* y12-y01              */

   S16 NEAR   dx0, dx1;

   if( tblPoints < 3 ) {
      return 0;
      }

   q =  tbl + tblPoints - 1;                    /* mark end of table             */
   x = CLIP(x, tbl[0].x, q->x);                 /* limit x to inside the table   */

   /* Find the trio of table points from which to interpolate x. This search selects
      x0,x1,x2 such that x is between x0 and x1. The exception to this is when
      x falls between the last 2 table coordinates, in which case x must be between
      x1,x2
   */
   for( p = q; (p > tbl) && (p->x > x); p-- );  /* Hunt back until x[n] < x or start of table      */
                                                /* search exits with p -> x0                       */
   q--;                                         /* mark to last entry but one                      */
   if( p >= q ) p = q - 1;                      /* if x0 > last-but-one then move x0 to 2 from end */

   /* Get 1st and 2nd diffs.

      To maintain resolution when computing quotients with integer arithmetic, scale up
      divisors first. When the quotients are used later to get the interpolant 'y'
      the product terms which include them are scaled back down.
   */
   y0 = p->y;   x0 = (p++)->x;
   y1 = p->y;   x1 = (p++)->x;
   y2 = p->y;   x2 = p->x;

   x01 = x1 - x0;
   x12 = x2 - x1;

   y12 = (_L(y2 - y1) << 8) / x12;              /* 1st diffs scaled << 8 */
   y01 = (_L(y1 - y0) << 8) / x01;

   y012 = (_L(y12 - y01) << 8) / (x01 + x12);   /* 2nd diff scaled << 16 */

   dx0 = x - x0;
   dx1 = x - x1;

   return ClipLongToInt( y0 +
                         ((_L(dx0) * _L(y01) ) >> 8) +       /* >> 8 to normalise for y01     */
                         (dx0 * dx1 * _L(y012) >> 16)        /* >> 16 to normalise for y012   */
                        );
}

#elif _TARGET_IS == TARGET_LIB_SMALL || _TARGET_IS == TARGET_LIB_CC430

PUBLIC S16 Interpolate2XY( S_XY CONST * tbl, S16 x, U8 tblPoints ) {

//   S_XY CONST * NEAR p, * NEAR q;            /* to scan the table */

   U8 p, q;

   S16 NEAR   y0, y1, y2, /* table entries        */
               x0, x1, x2;
   S16 NEAR    y01;   /* y2-y1 and y1-y0      */

   if( tblPoints < 3 ) {
      return 0;
      }

   q =  tblPoints - 1;                                /* mark end of table             */
   x = ClipInt(x, tbl[0].x, tbl[tblPoints - 1].x);    /* limit x to inside the table   */

   /* Find the trio of table points from which to interpolate x. This search selects
      x0,x1,x2 such that x is between x0 and x1. The exception to this is when
      x falls between the last 2 table coordinates, in which case x must be between
      x1,x2
   */
   for( p = q; p && (tbl[p].x > x); p-- );            /* Hunt back until x[n] < x or start of table      */
                                                      /* search exits with p -> x0                       */
   q--;                                               /* mark to last entry but one                      */
   if( p >= q ) p = q - 1;                            /* if x0 > last-but-one then move x0 to 2 from end */

   /* Get 1st and 2nd diffs.

      To maintain resolution when computing quotients with integer arithmetic, scale up
      divisors first. When the quotients are used later to get the interpolant 'y'
      the product terms which include them are scaled back down.
   */
   y0 = tbl[p].y;   x0 = tbl[p].x;
   y1 = tbl[p+1].y;   x1 = tbl[p+1].x;
   y2 = tbl[p+2].y;   x2 = tbl[p+2].x;

   y01 = (_L(y1 - y0) << 8) / (x1 - x0);

   return
   ClipLongToInt
   (  y0 +
      ((_L(x - x0) * _L(y01) ) >> 8) +       /* >> 8 to normalise for y01     */
      (
         (x - x0) * (x - x1) * _L((_L((_L(y2 - y1) << 8) / (x2 - x1) - y01) << 8)
         /
         ((x1 - x0) + (x2 - x1))) >> 16      /* >> 16 to normalise for y012   */
      )
   );
}

#else
   #error "Interpolate2XY().  Must define _TARGET_IS for this function"
#endif



// ----------------------------------------- eof -----------------------------------------------------
