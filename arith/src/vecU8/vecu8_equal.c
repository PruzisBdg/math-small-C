 /*-----------------------------------------------------------------------------------------
|
|  VecU8_Equal()
|
------------------------------------------------------------------------------------------*/

#include "arith.h"

PUBLIC bool VecU8_Equal(U8 const *a, U8 const *b, U8 cnt)
{
   U8  i;

   for( i = 0; i < cnt; i++ )
   {
      if(a[i] != b[i]) {
         return false;
      }
   }
   return true;
}


