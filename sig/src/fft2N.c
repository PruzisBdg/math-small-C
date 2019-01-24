#include "common.h"
#include "util.h"
#include "intrins.h"
#include <stdio.h>
#include <math.h>
#include "mathfunc.h"


typedef float T_FFTNum;
typedef U8 T_FFTIdx;

typedef struct
{
   T_FFTNum re, im;
   U8 flags;   
} T_FFTComplex;

#define _Swapped _BitM(0)

#define _Radix  5
#define _Points 32

#if sizeof(T_FFTIdx) == 1
   #define swapIdx bitRevU8
#else
   #define swapIdx bitRevU16
#endif

PRIVATE U8 CONST revNibble[] = 
   { 0x00, 0x08, 0x04, 0x0C, 0x02, 0x0A, 0x06, 0x0E, 0x01, 0x09, 0x05, 0x0D, 0x03, 0x0B, 0x07, 0x0F };

PRIVATE U8 bitRevU8(U8 n)
{
   return _swapnibble_(revNibble[LOW_NIBBLE(n)])  | revNibble[HIGH_NIBBLE(n)];
}

PRIVATE U16 bitRevU16(U16 n)
{
   return _swapbyte_(bitRevU8(LOW_BYTE(n)))  | bitRevU8(HIGH_BYTE(n));
}

PRIVATE U8 bitRevN_U8(U8 n, U8 bitSize)
{
   return bitRevU8(n << (8 - bitSize));
}

PRIVATE U8 bitRevN_U16(U16 n, U8 bitSize)
{
   return bitRevU16(n << (16 - bitSize));
}

PUBLIC void FFT2( T_FFTComplex *vec )
{
   T_FFTIdx DATA c, d;
   T_FFTNum n;
      
   
   for(c = 0; c < _Points; c++)           // For each point
   {
      d = bitRevN_U8(c, _Radix);          // d <- swap destination
      
      if(d != bitRevN_U8(d, _Radix) &&    // swap destination != source? AND
           !vec[d].flags)                 // destination wasn't already swapped
      {
         n = vec[c].re;                   // the exchange indices 'c' and 'd'             
         vec[c].re = vec[d].re;
         vec[d].re = n;
         vec[c].flags = _Swapped;         // and mark source as swapped, so won't be re-swapped (as a destination)
      }
   }
}
   T_FFTComplex pts[_Points];
   
   
void main(void)
{
   float a,b,p,q,e,f;
   
   S16 c, d;
   
   a = SineFP( 45.0*RADS_PER_DEG);
   b = CosFP( 275.0*RADS_PER_DEG);
   
   c = SineS16( (45.0/360.0) * 65536.0 );
   d = CosS16( (45.0/360.0) * 65536.0 );
   
   p = sin(45.0*RADS_PER_DEG);
   q = cos(275.0*RADS_PER_DEG);
   
   e = atan(0.3);
   f = ArctanFP(0.3);

   printf("%f %f %d %d %f\r\n", (float)a, (float)b, c, d, e );
}

#if 0
void main(void) 
{
   U8 c;


   for( c = 0; c < _Points; c++ )
      { pts[c].re = c; pts[c].im = 0; pts[c].flags = 0; }
   
   FFT2(&pts);
   
   printf("%x %x\r\n", 0x28, bitRevU8(0x28) );
}
#endif






 
