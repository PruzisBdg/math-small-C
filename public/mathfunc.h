/* --------------------------------------------------------------------------
|
|                Math Functions
|
|
|
|
|
|
|
|
----------------------------------------------------------------------------- */

#ifndef MATHFUNC_H
#define MATHFUNC_H

//#include "libs_support.h"
#include "GenericTypeDefs.h"


// Trig definitions
#define PI              3.141592654
#define HALFPI          1.570796327
#define TWOPI           6.283185307
#define RADS_PER_DEG    1.74532952E-2
#define DEGS_PER_RAD    57.29577951

// ------- Trig

// Any angle, radians. Float = 300usec, 22MHz single-cycle 8051
// Each uses both SineFP_90(), CosFP_90()
PUBLIC float SineFP(float x);
PUBLIC float CosFP(float x);

// 0 - 90deg, in radians. More compact if need only sin or only cos.
PUBLIC float SineFP_90(float x);
PUBLIC float CosFP_90(float x);

// Integer, using Binary Angle (BAM:  -180 to 180deg -> -32768 to +32768)
// Returns sin/cos scaled  -1.0 to 1.0 -> -32768 to 32768
// About 90usec, 22Mhz single-cycle 8051
PUBLIC S16 SineS16(S16 y);
PUBLIC S16 CosS16(S16 y);

PUBLIC float ArctanFP(float x);


// -------- Calculus

// Integration by Simpsons rule;
PUBLIC S32    SimpsonS16( S16(*f)(S16), S16 start, S16 intvl, S16 steps);
PUBLIC double SimpsonDouble( double(*f)(double), double start, double intvl, S16 steps);
PUBLIC float  SimpsonFloat( float(*f)(float), float start, float intvl, S16 steps);


// ---------- Misc / oddball

PUBLIC U16 RewireU16(U16 CONST *map, U16 n);

// --------- Powers / Surds.

PUBLIC float InvSqrtFP(float n);    // Is 0x5F3759DF.


#endif // MATHFUNC_H

// ------------------------------- eof ------------------------------------------
