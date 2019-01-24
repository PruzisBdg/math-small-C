/*---------------------------------------------------------------------------
|
|                    Fuzzy Logic Inference Engine
|
|  
|  This package supports the implementation of simple fuzzy logic inference
|  engines with the following characteristics:
|
|     1. Individual input membership functions may be trapezoidal, triangular or square
|
|     2. Rules are written 'inline' using _AND, _OR and _NOT constructs (see fuz1.h)
|
|     3. Outputs have a single value linked to each rule. The value of an output value is 
|        the rule-weighted mean of all the values.
|
|     4. _AND and _OR constructs are implemented using MIN / MAX (the simplest method)
|
|  Discussion:
|
|  The package is itself compact (300bytes in H8S2357) and executes quickly. The rules are
|  Written inline by the user. Simple rules are compact and will also execute quickly. In
|  commercial and academic products it is usual to encode the logic (rules) in a table 
|  produced by the front end design tool. The table typically contains AND/OR combinations 
|  for all membership functions. An 'inference engine' scans the table; this takes a lot
|  of horsepower if there are more than a few input variables. 
|
|  How to use it:
|
|  Its best to look at an example, but here are the steps:
|
|     - Definitions / Declarations
|
|        1. Define types membership functions (structures) e.g. hi/lo.mid
|
|        2. Declare (const) membership functions based on 1.
|
|        3. Make a list of input variables
|
|        4. Define mapping of membership functions to input variables using 
|           fuz_DEC_MembershipFuncList(). Often each input variable has its own
|           membership function, but not always, the same membership function can be
|           used by multiple inputs vars.
|
|        5. Define list(s) (struct) of rule outputs. There may be more than one
|           list.
|
|        6. Declare the mappings from rule outputs to crisp outputs. Each rule
|           output may have one or more crisp ouputs.
|
|     - Allocate storage for
|
|        - array of input variables
|        - membership variables
|        - rule outputs 
|
|     - At runtime
|
|        1. fuz_GetMemberShips() to get values of membership variables  for all inputs
|
|        2. Run the inline code for the rules
|
|        3. Run fuz_GetOutput() in each set of rule outputs to get the corresponding crisp
|           outputs
|
|--------------------------------------------------------------------------*/

#ifndef FUZZY_A_H
#define FUZZY_A_H

#include "math_common.h"

/* ------------------------- Token pasting ---------------------------------

   When a token paste is used directly in a macro, an argument is not checked
   for further expansion before being pasted (unlike when the argument is 
   concatenated). Embedding the paste itself in macro allows expansion prior
   to pasting.

   If one of the parms to cat() is itself a paste string (i.e "A ## B") we almost 
   always want the result of this paste to be checked for expansion prior to being 
   pasted (again). Embedding cat() in xcat() forces an expansion check; its safest 
   always to use xcat() unless you specifically don't want to expand.
*/
#ifndef cat
   #define cat(x,y)   x ## y
#endif

#ifndef xcat
   #define xcat(x,y)  cat(x,y)
#endif   

typedef S16 fuz_T_InS16;         // crisp input type
typedef S16 fuz_T_OutS16;        // crisp output type
typedef U8  fuz_T_LogicVal;      // internal fuzzy logic values (0.. 255 gives enough granularity
typedef U16 fuz_T_RuleSum;       // if 'fuz_T_LogicVal' is a U8, can be U16 else ulong

#define fuz_OutputMaxS16 MAX_S16
#define fuz_OutputMinS16 MIN_S16

#define fuz_InputMax MAX_S16
#define fuz_InputMin MIN_S16

// Must match the range of 'fuz_T_LogicVal' above
#define fuz_TRUE  MAX_U8
#define fuz_FALSE MIN_U8

// Fraction 0.. 1 to fuzzy logic value.
#define fuz_FracVal(n)  CLIP( ((fuz_T_LogicVal)(fuz_TRUE*(n))), fuz_FALSE, fuz_TRUE)

// Boolean to fuzzy
#define fuz_Bool(b)     ((fuz_T_LogicVal)((b) ? fuz_TRUE : fuz_FALSE))
#define fuz_NotBool(b)  ((fuz_T_LogicVal)((b) ? fuz_FALSE : fuz_TRUE))

// Fuzzy to boolean
#define fuz_ToBool(f)   ((BOOLEAN)(((f) > fuz_FracVal(0.5)) ? TRUE : FALSE))
#define fuz_ToBoolBit(f)   ((BIT)(((f) > fuz_FracVal(0.5)) ? TRUE : FALSE))

// trapezoidal input membership function
typedef struct {
   fuz_T_InS16 l,             // lower tail
               lt,            // lower corner
               ut,            // upper corner
               u;             // upper tail
   } fuz_S_InFuncS16;

// A list of memberships function for one input variable
typedef struct {
   fuz_S_InFuncS16 CONST *funcList;
   U8              numFuncs;
   } fuz_S_InMapS16;

#define fuz_DEF_InputMap(mapArray)   { (mapArray), RECORDS_IN(mapArray) }

#define fuz_DEC_MembershipFuncList(listName, listMembers, numItems)  \
PRIVATE fuz_S_InMapS16 dconst listName[] = {                                \
   xcat(Dupc, numItems)(fuz_DEF_InputMap, listMembers)               \
   };


// Declares a union of S_structName and and array of the structure elements
#define DEF_ArrayUnion(structName, arrayType)                                       \
   typedef union {                                                                  \
      xcat(S_, structName)  name;                                                 \
      arrayType             idx[sizeof(xcat(S_, structName))/sizeof(arrayType)];  \
      } xcat(U_, structName);

#define DEF_ArrayUnion_Root(rootName, structName, arrayType)                        \
   typedef union {                                                                  \
      xcat(rootName, xcat(_S_, structName))  name;                                \
      arrayType             idx[sizeof(xcat(rootName, xcat(_S_, structName)))/sizeof(arrayType)];  \
      } xcat(rootName, xcat(_U_, structName));

#define fuz_DEF_InputVarList(listName, listMembers, numVars)   \
                                                               \
   typedef struct {                                            \
      fuz_T_InS16 xcat(Lstc, numVars)(listMembers);            \
   } xcat(S_,listName);                                        \
                                                               \
   DEF_ArrayUnion( listName, fuz_T_InS16 )


// Input functions
PUBLIC fuz_T_LogicVal fuz_GetMemberShipS16   ( fuz_S_InFuncS16 CONST *m, fuz_T_InS16 x );
PUBLIC void           fuz_GetOneMembershipS16( fuz_S_InFuncS16 CONST *mList, fuz_T_LogicVal *mOut, fuz_T_InS16 x, U8 numFuncs );
PUBLIC void           fuz_GetMemberShipsS16  ( fuz_T_InS16  *in, fuz_T_LogicVal *mOut, fuz_S_InMapS16 CONST *l, U8 numVars );

// Logic Functions

#if _TOOL_IS == TOOL_RIDE_8051
   /* On 8-bit load-store MCU's, calling these small functions MaxU8() MinU8() is more compact 
      than in-lining  MIN(), MAX(). Thats because they reduce the number of load/stores.
   */
   #include "arith.h"
   #define        fuz_OR(a, b)   ( (fuz_T_LogicVal) MaxU8((a), (b)) )
   #define        fuz_AND(a, b)  ( (fuz_T_LogicVal) MinU8((a), (b)) )
#else
   #define        fuz_OR(a, b)   ( (fuz_T_LogicVal) MAX((a), (b)) )        // To avoid promotion from 'U8' to 'S16' as a result
   #define        fuz_AND(a, b)  ( (fuz_T_LogicVal) MIN((a), (b)) )        // of comparsions in MIN/MAX, force output type
#endif

#define        fuz_NOT(a)     ( (fuz_T_LogicVal) ((fuz_T_LogicVal)fuz_TRUE - (a)) )


// Output functions
PUBLIC fuz_T_OutS16 fuz_GetOutputS16( fuz_T_OutS16 CONST *outMap, fuz_T_LogicVal *rules, U8 numRules );


/* ---- Precanned Membership function templates

   Pack Pragma?
*/

typedef struct {
   fuz_T_LogicVal  below, near;
   } fuz_S_BelowOrNear;

typedef struct {
   fuz_T_LogicVal  below, near, above;
   } fuz_S_BelowNearAbove;

typedef struct {
   fuz_T_LogicVal  below, above;
   } fuz_S_BelowOrAbove;

typedef struct {
   fuz_T_LogicVal  near;
   } fuz_S_Near;

typedef struct {
   fuz_T_LogicVal  low;
   } fuz_S_Low;

typedef struct {
   fuz_T_LogicVal  high;
   } fuz_S_High;

typedef struct {
   fuz_T_LogicVal  low, high;
   } fuz_S_LoHi;

typedef struct {
   fuz_T_LogicVal  low, mid, high;
   } fuz_S_LoMidHi;
   
typedef struct {                    // is 'LoMidHi' reversed
   fuz_T_LogicVal  high, mid, low;
   } fuz_S_HiMidLo;
   


#if 0
DEF_ArrayUnion_Root( fuz, BelowOrNear,    fuz_T_LogicVal )
DEF_ArrayUnion_Root( fuz, BelowNearAbove, fuz_T_LogicVal )
DEF_ArrayUnion_Root( fuz, BelowOrAbove,   fuz_T_LogicVal )
DEF_ArrayUnion_Root( fuz, Near,           fuz_T_LogicVal )
DEF_ArrayUnion_Root( fuz, Low,            fuz_T_LogicVal )
DEF_ArrayUnion_Root( fuz, High,           fuz_T_LogicVal )
DEF_ArrayUnion_Root( fuz, LoHi,           fuz_T_LogicVal )
DEF_ArrayUnion_Root( fuz, LoMidHi,        fuz_T_LogicVal )
DEF_ArrayUnion_Root( fuz, HiMidLo,        fuz_T_LogicVal )
#else

typedef union {
    fuz_S_BelowOrNear name ;
    fuz_T_LogicVal idx [ sizeof ( fuz_S_BelowOrNear ) / sizeof ( fuz_T_LogicVal ) ] ;
    } fuz_U_BelowOrNear;
    
    
typedef union {
    fuz_S_BelowNearAbove name ;
    fuz_T_LogicVal idx [ sizeof ( fuz_S_BelowNearAbove ) / sizeof ( fuz_T_LogicVal ) ] ;
    } fuz_U_BelowNearAbove;
    
    
typedef union {
    fuz_S_BelowOrAbove name ;
    fuz_T_LogicVal idx [ sizeof ( fuz_S_BelowOrAbove ) / sizeof ( fuz_T_LogicVal ) ] ;
    } fuz_U_BelowOrAbove;
    
    
typedef union {
    fuz_S_Near name ;
    fuz_T_LogicVal idx [ sizeof ( fuz_S_Near ) / sizeof ( fuz_T_LogicVal ) ] ;
    } fuz_U_Near;
    
    
typedef union {
    fuz_S_Low name ;
    fuz_T_LogicVal idx [ sizeof ( fuz_S_Low ) / sizeof ( fuz_T_LogicVal ) ] ;
    } fuz_U_Low;
    
    
typedef union {
    fuz_S_High name ;
    fuz_T_LogicVal idx [ sizeof ( fuz_S_High ) / sizeof ( fuz_T_LogicVal ) ] ;
    } fuz_U_High;
    
    
typedef union {
    fuz_S_LoHi name ;
    fuz_T_LogicVal idx [ sizeof ( fuz_S_LoHi ) / sizeof ( fuz_T_LogicVal ) ] ;
    } fuz_U_LoHi;
    
    
typedef union {
    fuz_S_LoMidHi name ;
    fuz_T_LogicVal idx [ sizeof ( fuz_S_LoMidHi ) / sizeof ( fuz_T_LogicVal ) ] ;
    } fuz_U_LoMidHi;
    
    
typedef union {
    fuz_S_HiMidLo name ;
    fuz_T_LogicVal idx [ sizeof ( fuz_S_HiMidLo ) / sizeof ( fuz_T_LogicVal ) ] ;
    } fuz_U_HiMidLo;
    
    
#endif


// ====================== Byte-sized inference engine (for speed) =============================

// Byte-sized IO for speed
typedef U8 fuz_T_InU8;         // crisp input type
typedef U8 fuz_T_OutU8;        // crisp output type

#define fuz_OutputMaxU8 MAX_U8
#define fuz_OutputMinU8 MIN_U8

#define fuz_InputMaxU8 MAX_U8
#define fuz_InputMinU8 MIN_U8

// trapezoidal input membership function
typedef struct {
   fuz_T_InU8 l,             // lower tail
              lt,            // lower corner
              ut,            // upper corner
              u;             // upper tail
   } fuz_S_InFuncU8;

// A list of memberships function for one input variable
typedef struct {
   fuz_S_InFuncU8 CONST *funcList;
   U8              numFuncs;
   } fuz_S_InMapU8;

// Input functions
PUBLIC fuz_T_LogicVal fuz_GetMemberShipU8   ( fuz_S_InFuncU8 CONST *m, fuz_T_InU8 x );
PUBLIC void           fuz_GetOneMembershipU8( fuz_S_InFuncU8 CONST *mList, fuz_T_LogicVal *mOut, fuz_T_InU8 x, U8 numFuncs );
PUBLIC void           fuz_GetMemberShipsU8  ( fuz_T_InU8  *in, fuz_T_LogicVal *mOut, fuz_S_InMapU8 CONST *l, U8 numVars );

// Output functions
PUBLIC fuz_T_OutU8 fuz_GetOutputU8( fuz_T_OutU8 CONST *outMap, fuz_T_LogicVal *rules, U8 numRules );


// Floating point

PUBLIC float fuz_GetOutputFloat( float CONST *outMap, fuz_T_LogicVal *rules, U8 numRules );

#endif // FUZZY_A_H

// --------------------------------------- eof -------------------------------------------------
