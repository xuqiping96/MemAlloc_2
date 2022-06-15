#include <assert.h>
#include <stdlib.h>

#include "../src/memory.h"

#define ADDRESS 0x28ff44

int main()
{
   assert(!mem_init(4096, FIRST_FIT));

   void *data[4];

   data[0] = mem_alloc(4);
   mem_dump();

   data[1] = mem_alloc(8);
   mem_dump();

   assert(!mem_free(data[0]));
   mem_dump();

   assert(!mem_free(data[1]));
   mem_dump();

   data[2] = mem_alloc(16);
   mem_dump();

   data[3] = mem_alloc(4);
   mem_dump();

   assert(!mem_free(data[2]));
   mem_dump();

   assert(!mem_free(data[3]));
   mem_dump();

   assert(mem_free((void *)ADDRESS));
   mem_dump();

   exit(0);
}
