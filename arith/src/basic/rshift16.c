#include "common.h"

PUBLIC S16 RShift16( S32 n )
{
   #if _TOOL_IS == TOOL_RIDE_8051

   #pragma ASM
   mov   A,R4
   mov   R6,A
   mov   A,R5
   mov   R7,A
   ret
   #pragma ENDASM
   return;

   #else
   return (S16)(n >> 16);
   #endif  
} 
