#include "bldcfg.h"
#include "common.h"
#include "mathfunc.h"

/*-----------------------------------------------------------------------------------------
|
|  SineS16()
|
|  Return sin(x) for 'x' in Binary Angle Measure (BAM).
|
|		BAM:  0 = 0deg,  0x7FFF = 180deg,  0x8000 = -180deg
|
|	Return sin(x), scaled -1.0 - 1.0  -> -32768 -> 32768
|
|	From
|
|                    x^3    x^5    x^7    x^9
|		sin(x)  =  x - ---  + ---  - ---  + ---
|                     3!     5!     7!     9!
|
|	using Horner form
|
|                  x^2       x^2      x^2       x^2
|    sin(x)  = ((((---  - 1) --- + 1) ---  - 1) --- + 1) * x
|                  9*8       7*6      5*4       3*1
|
|	About 100usec on 22MHz single-cycle 8051
|
------------------------------------------------------------------------------------------*/

PUBLIC S16 SineS16(S16 y)
{
   #define s1 0x6488
   #define s3 0x2958
   #define s5 0x51A
   #define s7 0x4D
   
   S32 z;
   
   z = ((S32)y * y) >> 12;   
   return (y * (s1 - ((z * (s3 - ((z * (s5 - ((z * s7) >> 16))) >> 16))) >> 16))) >> 13;
}

// --------------------------------- eof -------------------------------------
 
