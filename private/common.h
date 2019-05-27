/* ---------------------------------------------------------------------
|
|--------------------------------------------------------------------------*/
#ifndef DET_COMMON_H
#define DET_COMMON_H

#include "bldcfg.h"


/* ----------------------- Basic Types -------------------------- */

typedef  unsigned char        U8;
typedef  signed   char        S8;
typedef  unsigned short int   U16;
typedef  signed   short int   S16;
typedef  unsigned long        U32;
typedef  signed   long        S32;
//typedef  unsigned char        BOOLEAN;

typedef  unsigned char        BYTE;
typedef  unsigned int         WORD;
typedef  unsigned long        DWORD;
typedef  signed   char        S_BYTE;
typedef  signed   int         S_WORD;
typedef  signed   long        S_DWORD;


/* ------------------------- Number Limits ------------------------------ */

#define MAX_UCHAR (255)
#define MIN_UCHAR (0)

#define MAX_CHAR  (127)
#define MIN_CHAR  (-128)

#define MAX_INT   (32767)
#define MIN_INT   (-32768)

#define MAX_UINT  (65535)
#define MIN_UINT  (0)

#define MAX_LONG  ((long)( 2147483647))
#define MIN_LONG  ((long)(-2147483648))

#define MAX_WORD  (65535)
#define MIN_WORD  (0)




/* --------------------------- Compound Types ------------------------- */

typedef  union
{
   DWORD    dw;
   S_DWORD  sdw;
   WORD     w[2];    /* access with WORD_MSB and WORD_LSB   */
   S_WORD   sw[2];   /* access with WORD_MSB and WORD_LSB   */
   BYTE     b[4];    /* access with LONG_HMSB, LONG_HLSB,   */
   S_BYTE   sb[4];   /*  LONG_LMSB, and LONG_LLSB           */
}  DWORD_BYTES;

typedef union { WORD w; int i; BYTE b[2]; } BYTES;

/* assumes Hitachi/Motorola style */
#define  WORD_MSB    0                 /* big end at [0] */
#define  WORD_LSB    1
#define  LONG_HMSB   0                 /* big end at [0] */
#define  LONG_HLSB   1
#define  LONG_LMSB   2
#define  LONG_LLSB   3


/* ------------------------- Byte / Nibble Accesss ---------------------- */

#define HIGH_BYTE(n) ((U8)((n) >> 8))
#define LOW_BYTE(n)  ((U8)((n) & 0xFF))

#define LOW_NIBBLE(b)  ((U8)((b) & 0x0F))
#define HIGH_NIBBLE(b)   ((U8)(((b) >> 4) & 0x0F))




/* ------------------------- Scope -------------------------------------- */

#define PUBLIC
#define PRIVATE static


//#define NULL ((void *) 0U)

/* ------------------- Token Pasting --------------------------------------

   When a token paste is used directly in a macro, an argument is not checked
   for further expansion before being pasted (unlike when the argument is
   concatentated). Embedding the paste itself in macro allows expansion prior
   to pasting.
*/
#define CAT(x,y)  x##y
#define XCAT(x,y)  CAT(x,y)


/* ------------------------ Arithmetic --------------------------------------- */

#define MAX(a,b)  ((a) > (b) ? (a) : (b))
#define MIN(a,b)  ((a) < (b) ? (a) : (b))
#define ABS(n)    ((n) < 0 ? -(n) : (n))
#define MEAN(a,b) (((a)+(b))/2)

#define CLIP(n, min, max) (((n)<(min))?(min):(((n)>(max))?(max):(n)))
#define RECORDS_IN(a)  (sizeof(a)/sizeof((a)[0]))
#define INSIDE_LIMITS(n, min, max)   (((n) > (min)) && ((n) < (max)))
#define OUTSIDE_LIMITS(n, min, max)   (((n) < (min)) || ((n) > (max)))


/* ---------------------------- Bits / Flags ------------------------------------ */

/* To manipulate a bit at a given (bit) position */
#define _BitM(bit) (1 << (bit))
#define _notB(bit)  0

/*   To manipulate bits with a bit mask.  */
#define SETB(reg,mask) {(reg) |= (mask);}
#define CLRB(reg,mask) {(reg) &= ~(mask);}

#define BSET(reg,mask) ((reg) & (mask))
#define BCLR(reg,mask) (!((reg) & (mask)))

#define SGN(v)       ((v)>0?1:((v)==0?0:-1))
#define ALL_SET(v,m) (((v)&(m))==(m))
#define ANY_SET(v,m) (((v)&(m))!=0)
#define NOT_SET(v,m) (((v)&(m))==0)


/* ------------------------- Bit fields. ------------------------------- */

#define WR_FIELD( v, n )             { (v) |= (n); }
#define RD_FIELD( v, mask )          ((v) & (mask))

#define CLR_FIELD( v, mask )         { (v) &= ~(mask); }
#define SET_FIELD( v, mask )         WR_FIELD( v, mask) )
#define OR_INTO_FIELD( v, mask, n )  {(v) |= ((n) & (mask)); }
#define CLR_FIELD_WR( v, mask, n )   { (v) |= ( ((v) & ~(mask)) | ((n) & (mask)) ); }
#define FIELD_EQUALS( v, mask, n )   ( RD_FIELD(v, mask) == (n) )


/* ------------------------ Boolean ------------------------------------ */

#define TRUE     1
#define FALSE    0

/* Numeric-to-Boolean conversion */
#define _BOOL(n)  (((n)==0)?FALSE:TRUE)
#define _NotBOOL(n)  (((n)==0)?TRUE:FALSE)


#endif // DET_COMMON_H

// ---------------------------------------- eof -------------------------------------------
