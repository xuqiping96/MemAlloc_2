#include <assert.h>
#include <stdlib.h>

#include "../src/memory.h"

int main()
{
   assert(!mem_init(4096, FIRST_FIT));

   void *data[4];

   data[0] = mem_alloc(800);
   assert(data[0]);

   data[1] = mem_alloc(800);
   assert(data[1]);

   data[2] = mem_alloc(800);
   assert(data[2]);

   data[3] = mem_alloc(800);
   assert(data[3]);

   while (mem_alloc(800))
      ;

   assert(!mem_free(data[1]));
   assert(!mem_free(data[2]));

   data[2] = mem_alloc(1600);
   assert(data[2]);

   exit(0);
}
