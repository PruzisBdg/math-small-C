#include "common.h"

PUBLIC void CopyInts( S16 *dest, S16 const *src, U16 cnt )
{
   for( ; cnt; cnt-- ) *dest++ = *src++;
}


 
