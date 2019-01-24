#include "bldcfg.h"
#include "common.h"
#include "mathfunc.h"

/*-----------------------------------------------------------------------------------------
|
|  CosS16()
|
|  Return cos(x) for 'x' in Binary Angle Measure (BAM).
|
|		BAM:  0 = 0deg,  0x7FFF = 180deg,  0x8000 = -180deg
|
|	Return cos(x), scaled -1.0 - 1.0  -> -32768 -> 32768
|
|                    x^2    x^4    x^6    x^8
|		cos(x)  =  1 - ---  + ---  - ---  + ---
|                     2!     4!     6!     8!
|
|	using the Horner form
|
|                  x^2       x^2      x^2       x^2
|    cos(x)  =  (((---  - 1) --- + 1) ---  - 1) --- + 1
|                  8*7       6*5      4*3       2*1
|
|	About 100usec on 22MHz single-cycle 8051
|
------------------------------------------------------------------------------------------*/

PUBLIC S16 CosS16(S16 y)
{
   #define c0 0x7FFF
   #define c2 0x4EF5
   #define c4 0x103E
   #define c6 0x156
   
   S32 z;
   
   z = ((S32)y * y) >> 12;   
   return c0 - ((z * (c2 - ((z * (c4 - ((z * c6) >> 16))) >> 16))) >> 15);
}


// --------------------------------- eof -------------------------------------
  
