#include <assert.h>
#include <stdlib.h>
#include <stdint.h>

#include "../src/memory.h"

int main()
{
   assert(!mem_init(4096, FIRST_FIT));

   int *data = (int *)mem_alloc(sizeof(int));
   assert(data);
   assert(!((int)data % 4));

   exit(0);
}
