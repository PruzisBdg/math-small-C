
#include <stdio.h>
#include "arith.h"
#include "unity.h"

int main(void)
{
   S16 exp = 44;

   printf("GetPwr10Double(%d) = %e\r\n", exp,  GetPwr10Double(44));

   TEST_ASSERT_EQUAL_DOUBLE( 1E15, GetPwr10Double(15));
}
