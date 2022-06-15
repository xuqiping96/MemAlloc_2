#include <assert.h>
#include <stdlib.h>

#include "../src/memory.h"

int main()
{
   assert(!mem_init(4096, FIRST_FIT));
   assert(!mem_alloc(4095));

   exit(0);
}
