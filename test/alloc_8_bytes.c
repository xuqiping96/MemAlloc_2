#include <assert.h>
#include <stdlib.h>

#include "../src/memory.h"

int main()
{
   assert(!mem_init(4096, FIRST_FIT));

   mem_dump();

   void *data = mem_alloc(8);
   mem_dump();
   assert(data);

   exit(0);
}
