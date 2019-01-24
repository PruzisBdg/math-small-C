#include "arith.h"
#include "iirfilt1.h"

typedef struct
{
   S_IIR1  lpass;
   S16     minDiff;
} S_SlewLimit;

// ---------------------------------- eof ----------------------------------------
