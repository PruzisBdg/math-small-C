/*---------------------------------------------------------------------------
|
|                Fuzzy Logic with trapezoidal memberships
|                           8-bit unsigned version (U8)
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
|  written inline by the user. Simple rules are compact and will also execute quickly. In
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
|        
|--------------------------------------------------------------------------*/

#include "fuzzy_a.h"
#include "arith.h"



/* ========================== Inputs -> Memberships ============================ */

/* --------------------------------- getMU8 --------------------------------- */

PRIVATE fuz_T_LogicVal getMU8(fuz_T_InU8 l, fuz_T_InU8 u, fuz_T_InU8 x)
{
   return AmulBdivC_U8(fuz_TRUE, x-l, u-l);
}

/* ----------------------------- fuz_GetMemberShipU8 ------------------------------ */

PUBLIC fuz_T_LogicVal fuz_GetMemberShipU8( fuz_S_InFuncU8 CONST *m, fuz_T_InU8 x ) {
   
   if( x < m->l || x > m->u )
      { return fuz_FALSE; }
   else if ( x < m->lt )
      { return getMU8( m->l, m->lt, x); }
   else if ( x < m->ut )
      { return fuz_TRUE; }
   else
      { return fuz_TRUE - getMU8( m->ut, m->u, x); }
}

/* ----------------------------- fuz_GetOneMembershipU8 ------------------------------ */

PUBLIC void fuz_GetOneMembershipU8( fuz_S_InFuncU8 CONST *mList, fuz_T_LogicVal *mOut, fuz_T_InU8 x, U8 numFuncs ) {

   for( ; numFuncs; numFuncs--, mList++, mOut++ ) 
   {
      *mOut = fuz_GetMemberShipU8( mList, x );
   }
}

/* ----------------------------- fuz_GetMemberShipsU8 ------------------------------ */

PUBLIC void fuz_GetMemberShipsU8( fuz_T_InU8 *in, fuz_T_LogicVal *mOut, fuz_S_InMapU8 CONST *l, U8 numVars ) {

   for( ; numVars; numVars--, mOut += l->numFuncs, l++, in++ ) {
      fuz_GetOneMembershipU8( l->funcList, mOut, *in, l->numFuncs );
      }
}


/* ======================= end: Byte-sized Inputs -> Memberships =============================== */


/* ======================= Byte-sized Rule outputs => Crisp Results ============================= 

   'Crisp' output is the output value assigned for each rule, weighted by the rule
   strength.
*/
PUBLIC fuz_T_OutU8 fuz_GetOutputU8( fuz_T_OutU8 CONST *outMap, fuz_T_LogicVal *rules, U8 numRules ) {

   fuz_T_RuleSum     ruleSum;
   fuz_T_LogicVal    r;
   U16               outSum, errSum;
   U8                c;
   fuz_T_OutU8    n;

   for( c       = numRules, 
        errSum  = 0, 
        ruleSum = 0, 
        outSum  = 0; 
        c; 
        c--, outMap++, rules++ ) 
   {
      r = *rules;
      ruleSum += r;
      n = *outMap;
      outSum += r * (U16)n;               // accumulate rule-weighted sum
      errSum += n;                        // but also accumulate non-weighted in case no rules fire.
   }
   /* If rules fired enough then return the rule-weighted average of the outputs.
      It they didn't then you have a 'hole' in the logic surface. As a best guess 
      return the mean of the outputs
   */
   if( ruleSum > fuz_FracVal(0.1) )       // rules fired enough?
      { return outSum / ruleSum; }        // then return rule-weighted outputs
   else
      { return errSum / numRules; }       // else, for safety, return mean of outputs 
}


/* ==================== end:  Byte-sized Rule outputs => Crisp Results ============================= */


// ---------------------------------- eof ------------------------------------------------
