#include "common.h"

PUBLIC void FillBytes( U8 *dest, U8 n, U16 cnt )
{
   for( ; cnt; cnt-- ) *dest++ = n;
}

 
