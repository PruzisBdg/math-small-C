/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_MakeMultiple
|
|  Make the list of vectors 'l', list size is 'numVecs'
|
|  PARAMETERS:    'l'            the vectors to be made
|
|  RETURNS:
|     
|
|	DATE        AUTHOR            DESCRIPTION OF CHANGE 
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

#include "vec.h"

PUBLIC void Vec_MakeMultiple( S_VecCfg CONST *l, U8 numVecs )
{
   S_VecCfg CONST * LVAR p;

   for( p = l; numVecs; numVecs--, p++ )
   {
      _Vec_Make( p->vec, p->buf, p->rows, p->cols );
   }
}

// ---------------------------------- eof -----------------------------------------------------
