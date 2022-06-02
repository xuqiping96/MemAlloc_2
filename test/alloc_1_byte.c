#include <assert.h>
#include <stdlib.h>

#include "memory.h"

int main()
{
   assert(!mem_init(4096, FIRST_FIT));

   mem_dump();

   void *data = mem_alloc(1);
   mem_dump();
   assert(data);

   exit(0);
}
