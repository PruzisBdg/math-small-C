/* ------------------------- Linterp_YTbl ----------------------------------

   Linear interpolation on a fixed-interval table. The X-scale is 256 counts
   per point. The interpolation is clipped to inside the table.
   
   Not as accurate as Interpolate2(), which uses forward differences, but 
   faster and more compact.
*/
#include "common.h"
#include "arith.h"

PRIVATE S16 interp2(S16 CONST *p, U8 mix)
{
   return MixS16(p[0], p[1], mix);     // Return linear interpolation between adjacent points
}

PUBLIC S16 Linterp_YTbl( S16 CONST *tbl, S16 x, U8 tblPoints ) 
{

   return 
   x < 0                                           // Below table?                
   ?
      tbl[0]                                       // then return bottom
   :
      (
         HIGH_BYTE(x) >= tblPoints-1               // At end of or above table?
         ?
            tbl[tblPoints-1]                       // then return top
         :
            interp2(&tbl[HIGH_BYTE(x)], LOW_BYTE(x)) // else linearly interpolate between two table points
      );
}


// --------------------------------------- eof -------------------------------------------
   
