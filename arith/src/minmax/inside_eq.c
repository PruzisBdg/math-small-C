#include "common.h"
#include "arith.h"

PUBLIC BIT Inside_U8(U8 a, U8 min, U8 max)
   { return a > min && a < max ? 1 : 0; }

PUBLIC BIT InsideEq_U8(U8 a, U8 min, U8 max)
   { return a >= min && a <= max ? 1 : 0; }

PUBLIC BIT Inside_S8(S8 a, S8 min, S8 max)
   { return a > min && a < max ? 1 : 0; }

PUBLIC BIT InsideEq_S8(S8 a, S8 min, S8 max)
   { return a >= min && a <= max ? 1 : 0; }

PUBLIC BIT Inside_U16(U16 a, U16 min, U16 max)
   { return a > min && a < max ? 1 : 0; }

PUBLIC BIT InsideEq_U16(U16 a, U16 min, U16 max)
   { return a >= min && a <= max ? 1 : 0; }

PUBLIC BIT Inside_S16(S16 a, S16 min, S16 max)
   { return a > min && a < max ? 1 : 0; }

PUBLIC BIT InsideEq_S16(S16 a, S16 min, S16 max)
   { return a >= min && a <= max ? 1 : 0; }

PUBLIC BIT Inside_U32(U32 a, U32 min, U32 max)
   { return a > min && a < max ? 1 : 0; }

PUBLIC BIT InsideEq_U32(U32 a, U32 min, U32 max)
   { return a >= min && a <= max ? 1 : 0; }

PUBLIC BIT Inside_S32(S32 a, S32 min, S32 max)
   { return a > min && a < max ? 1 : 0; }

PUBLIC BIT InsideEq_S32(S32 a, S32 min, S32 max)
   { return a >= min && a <= max ? 1 : 0; }

// ----------------------------- eof -------------------------------------

