/* -----------------------------------------------------------------
|
|              Integer Arithmetic with inherent 64bit types
|
--------------------------------------------------------------------- */

#include "spj_stdint.h"
#include "libs_support.h"
#include "arith.h"

// ------------------------------------------------------------------------------
PUBLIC S64 AplusBS64(S64 a, S64 b)
{
    return
        (a > 0 && b > 0 && (a+b) < 0)                   // Overflow?
            ? MAX_S64
            : ( (a < 0 && b < 0 && (a+b) > 0) ||        // Underflow?
                (a == MIN_S64 && b == MIN_S64)          // Rollover twice so will miss test above.
                ? MIN_S64
                : a + b );
}

// ------------------------------------------------------------------------------
PUBLIC S64 AminusBS64(S64 a, S64 b)
{
   return
        a > b
            ? (a-b < 0
                ? MAX_S64
                : a-b)
            : (a-b > 0
                ? MIN_S64
                : a-b);
}

// ------------------------------------------------------------------------------
PUBLIC U64 AplusBU64(U64 a, U64 b)
{
    U64 c = a + b;
    return
        c >= a && c >= b
            ? c
            : MAX_U64;
}

// ------------------------------------------------------------------------------
PUBLIC U64 AminusBU64(U64 a, U64 b)
{
    return
        a > b
           ? a - b
           : 0;
}

// ------------------------------------------------------------------------------
PUBLIC U64 ClipU64(U64 n, U64 min, U64 max)
{
    return
        min > max                                       // Limits are crossed?
            ? ((min >> 1) + (max >> 1))                 // then return mean of limits
            : (n > max ? max : (n < min ? min : n));    // else clip 'n' to limits.
}

// ------------------------------------------------------------------------------
PUBLIC S64 ClipS64(S64 n, S64 min, S64 max)
{
    return
        min > max                                       // Limits are crossed?
            ? ((min >> 1) + (max >> 1))                 // then return mean of limits
            : (n > max ? max : (n < min ? min : n));    // else clip 'n' to limits.
}

// ------------------------------------------------------------------------------
PUBLIC U64 MaxU64(U64 a, U64 b) { return a > b ? a : b; }
PUBLIC S64 MaxS64(S64 a, S64 b) { return a > b ? a : b; }
PUBLIC U64 MinU64(U64 a, U64 b) { return a > b ? b : a; }
PUBLIC S64 MinS64(S64 a, S64 b) { return a > b ? b : a; }

// ------------------------------------------------------------------------------
PUBLIC U32 ClipU64toU32(U64 n)
	{ return n > MAX_U32 ? MAX_U32 : n; }

// ------------------------------------------------------------------------------
PUBLIC U32 ClipS64toU32(S64 n)
	{ return n > MAX_U32 ? MAX_U32 : (n < 0 ? 0 : n); }

// ------------------------------------------------------------------------------
PUBLIC S32 ClipS64toS32(S64 n)
	{ return n > MAX_S32 ? MAX_S32 : (n < MIN_S32 ? MIN_S32 : n); }

// ---- via U64 -------------------------------------------------------------------
PUBLIC U32 AmulBdivC_U32(U32 a, U32 b, U32 c)
{
    return
        a == 0 || b == 0
        ? 0
        : ( c == 0
            ? MAX_U32
            : ClipU64toU32(a * (U64)b / c));
}

// ------------------------------------------------------------------------------
PUBLIC S64 MulS32(S32 a, S32 b) { return b * (S64)a; }


// ---------------------------- eof -------------------------------------

