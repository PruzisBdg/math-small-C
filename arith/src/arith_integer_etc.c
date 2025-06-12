/* -----------------------------------------------------------------
|
|              Basic Integer Arithmetic
|
--------------------------------------------------------------------- */

#include "common.h"
#include "arith.h"

PUBLIC S16 AbsS16(S16 n)
{
   return
      n == MIN_S16        // Gotta watch that sign inversion!
         ? MAX_S16
         : (n < 0 ? -n : n);
}

PUBLIC U16 AbsDiffS16(S16 a, S16 b)
    {return (U16)(a > b ? (S32)a - b : (S32)b - a); }

PUBLIC S16 ClipS32toS16(S32 n)
    { return (n > MAX_S16) ? MAX_S16 : (n < MIN_S16 ? MIN_S16 : n); }

PUBLIC S8 ClipS16toS8(S16 n)
    { return (n > MAX_S8) ? MAX_S8 : (n < MIN_S8 ? MIN_S8 : n); }

PUBLIC S16 SqS8(S8 a) { return (S16)a * a; }

PUBLIC U32 AplusBU32(U32 a, U32 b)
{
    return
        (U32)(a + b) < a || (U32)(a + b) < b || (a+b) > MAX_U32
            ? MAX_U32
            : a + b;
}

PUBLIC U8 ClipU16toU8(U16 n)
    { return n > MAX_U8 ? MAX_U8 : n; }

PUBLIC U16 MaxU16(U16 a, U16 b)
    { return a > b ? a : b; }

PUBLIC U16 MinU16(U16 a, U16 b)
    { return a < b ? a : b; }

PUBLIC S16 MaxS16(S16 a, S16 b)
    { return a > b ? a : b; }

PUBLIC U16 AmulBdivC_U16(U16 a, U16 b, U16 c)
{
    return
        c == 0
            ? (a == 0 || b ==0
                ? 0
                : MAX_U16)
            : ClipU32toU16(a * (U32)b / c);
}

PUBLIC U8 MinU8(U8 a, U8 b)
    { return a < b ? a : b; }

PUBLIC U16 AminusBU16(U16 a, U16 b)
    { return a > b ? a - b : 0; }

PUBLIC U16 ClipU32toU16(U32 n)
    { return (n > MAX_U16) ? MAX_U16 : n; }

PUBLIC S16 AplusBS16(S16 a, S16 b)
    { return ClipS32toS16(a + (S32)b); }

PUBLIC U8 AminusBU8(U8 a, U8 b)
    { return a > b ? a - b : 0; }



PUBLIC S16 AmulBdivC_S16_U8_U8(S16 a, U8 b, U8 c)
{
    /* This function is often used for taking simple fractions e.g b = 3, c = 16. So check
       if 32 bit arithmetic is need. Stay with faster 16bit if it's not.
    */
    return
        c == 0
            ? (a == 0 || b == 0
                ? 0
                : (a > 0 ? MAX_S16 : MIN_S16))
            : (
            ((a < 4096 && a > -4096) && (b < 8)) ||         // a * b fits inside 16bit int? OR
            ((a < 1024 && a > -1024) && (b < 32))           // a * b fits this way
                ? a * b / c                                 // then do 16 bit arithmetic
                : ClipS32toS16(a * (S32)b / c));             // else fall back to a 32bit product.

}

PUBLIC U16 AmulBdivC_U16_rnd(U16 a, U16 b, U16 c)
{
    return
        c == 0
            ? (a == 0 || b ==0
                ? 0
                : MAX_U16)
            : ClipU32toU16( ((a * (U32)b) + (c/2)) / c);
}



PUBLIC U16 IncrU16(U16 *n)
{
   if(*n < MAX_U16)
   {
      (*n)++;
   }
   return *n;
}

PUBLIC U32 IncrU32(U32 *n)
{
   if(*n < MAX_U32)
   {
      (*n)++;
   }
   return *n;
}

PUBLIC U32 MinU32(U32 a, U32 b)
    { return a < b ? a : b; }

PUBLIC U32 U32plusS16(U32 a, S16 b)
{
	return
		b > 0
			? AplusBU32(a, b)
			: AminusBU32(a, -b);
}

PUBLIC U8 AplusBU8(U8 a, U8 b)
    { return a + (U16)b > MAX_U8 ? MAX_U8 : a + b; }

PUBLIC S16 ClipS16(S16 n, S16 min, S16 max)
{
    return
        min > max                                       // Limits are crossed?
            ? ((min >> 1) + (max >> 1))                 // then return mean of limits
            : (n > max ? max : (n < min ? min : n));    // else clip 'n' to limits.
}


PUBLIC U32 SqU16(U16 n) { return (U32)n * n; }


/* ----------------------------- SqrtU32 ---------------------------------------

   Returns the square root of the absolute value of 'n'. Uses successive aproximation.
   Will terminate in 16 loops or less.
*/
PUBLIC U16 SqrtU32(U32 n)
{

   U32   u;
   U16   root, step;

   if( n == 0 ) return 0;

   for( root = 32768U, step = 16384U, u = 32768LU * 32768LU; step > 0; step >>= 1 ) {
        root = u > n
                ? root - step
                : root + step;

        u = root * (U32)root;
        }
  // Adjust SAR result for equi-sized bins, centered on exact root.
  return
    n > u + root && root != MAX_U16 // Bin-up? (except 65535 we are already at top)
        ? root+1
        : (n < u - root             // Bin down?
            ? root-1
            : root);                // else already correctly binned; leaver unchanged.
}


PUBLIC U8 U8PtrDiff_toU8(U8 const *a, U8 const *b) {
   return
      a <= b
         ? 0
         : ( (a - b) > 0xFF
            ? 0xFF
            : a - b); }






// --------------------------- eof -----------------------------------


