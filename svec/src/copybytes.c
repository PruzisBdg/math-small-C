#include "common.h"

PUBLIC void CopyBytes( U8 *dest, U8 const *src, U16 cnt )
{
   for( ; cnt; cnt-- ) *dest++ = *src++;
}

 
