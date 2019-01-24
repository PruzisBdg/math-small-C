/* -------------------------------------------------------------------------
|
|  Integer IIR Filter - Multiple 2nd order sections - parallel
|   
|
|
|
|
|
|   
|      Rev 1.0   May 19 2009 12:56:24   spruzina
|   Initial revision.
|  
----------------------------------------------------------------------------- */

#ifndef IIRFILT_H
#define IIRFILT_H

/* If basic types are supplied by the Host project instead \public\common.h then don't 
   resupply them from common.h.
*/ 
#ifndef _BASIC_TYPES_FROM_HOST_PROJECT
   #include "math_common.h"
#endif


#define _IIR_Mem  /* Memory space control - Must match where filter is made */

/* -------------------- iir2_:  2nd-order IIR Filter ---------------------

   Has 2 numerators, 2 denominators
*/

typedef struct {
   S32         buf[2];     /* accumulators 32bit                        */
   S16 CONST   *coffs;     /* coffs 16bit                               */
   U8          tapIdx,     /* indexes most recent sample in the buffer  */
               coffsPwr2;  /* coefficients scale as a power of 2        */
   } iir2_S;

/* 2 denominators (B1, B2) + 3 numerators (A0.. A2). B0 always equals '1' 
   so doesn't have to be in the coffs list.
*/
#define iir2_CoffsPerSection 5

typedef struct {
   S16  coffs[iir2_CoffsPerSection];
   } iir2_S_Coffs;

extern void iir2_Init( iir2_S _IIR_Mem *f, S16 CONST *coffs, U8 coffsScalePwr2 );
extern S16  iir2_Run(  iir2_S _IIR_Mem *f, S16 in );

/* ------------------------ end: iir2_ ---------------------------------------- */






/* ------------- iirNx2_: multiple 2nd order sections - parallel ----------------------- */

typedef struct {
   iir2_S _IIR_Mem   *iir2;          /* the 2nd order sections  */
   U8                numSections;    /* how many                */
   } iirNx2_S;


/* Wrappers for 4th, 6th and 8th order filters - the commonest for us. */
typedef struct {
   iirNx2_S  filt;
   iir2_S    sections[2];
   } iir2x2ndPar_S;

typedef struct {
   iirNx2_S  filt;
   iir2_S    sections[3];
   } iir3x2ndPar_S;

typedef struct {
   iirNx2_S  filt;
   iir2_S    sections[4];
   } iir4x2ndPar_S;


PUBLIC void iirNx2_Init( iirNx2_S _IIR_Mem *f, 
                         iir2_S _IIR_Mem *iir2Blocks, 
                         iir2_S_Coffs CONST *coffs,
                         U8 coffsScalePwr2,
                         U8 numSections );

PUBLIC S16  iirNx2P_Run(  iirNx2_S _IIR_Mem *f, S16 in );



/* --------------------------- end: iirNx2_ --------------------------------------- */


/* ------------------ Vector IIR; each section multiple-2nd-order -------------------- */

// 2-section Init/Run
PUBLIC void iir2x2ndVec_Init( iir2x2ndPar_S _IIR_Mem *f,             // Init this vector-filter 
                              iir2_S_Coffs  CONST    *coffs,         // each channel has the same coffs
                              U8                     coffsScalePwr2, // which are scaled thus
                              U8                     vecSize );

PUBLIC void iir2x2ndVec_Run( iir2x2ndPar_S _IIR_Mem  *f,           // Run this vector-filter 
                             S16           _IIR_Mem  *in,          // from here
                             S16           _IIR_Mem  *out,         // to here
                             U8                      vecSize );

#endif /* IIRFILT_H  */

/* ---------------------------------- eof ----------------------------------------- */
