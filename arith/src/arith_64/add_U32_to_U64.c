#include "common.h"
#include "arith.h"
#include <intrins.h>

#define HIGH_WORD(n)  ((U16)((n) >> 16))
#define LOW_WORD(n)   ((U16)(n))

typedef union
{
   U16 us[4];   
} S_U64; 


PRIVATE U16 highWord(U32 n)
{
   return *((U16 const *)&n);
}

#define _highWord(n)  _lror_((n), 16)


PRIVATE U32 getU32(U16 const *d)
{
   return *((U32 const *)d);
}

#define _getU32(d)  (*((U32*)(d)) )

PRIVATE void putU32(U16 *d, U32 n)
{
   *((U32 *)d) = n;
}

#if 0
PUBLIC U32 MulU16(U16 a, U16 b) 
{ 
   return MulS16(a, b) >> 16; 
}
#endif

PUBLIC void AddS32ToS64(S_U64 *sum, U32 n)
{
   U32 r;

   r = _getU32(&sum->us[0]) + LOW_WORD(n);
   sum->us[0] = LOW_WORD(r);
   r = _highWord(r) + _highWord(n) + _getU32(&sum->us[1]);
   sum->us[1] = LOW_WORD(r);
   r = _highWord(r) + _getU32(&sum->us[2]);
   sum->us[2] = LOW_WORD(r);
   sum->us[3] = _highWord(r) + _getU32(&sum->us[3]);   
}


