#include <assert.h>
#include <stdlib.h>

#include "memory.h"

#define DATA 0x12345678

int main()
{
   assert(!mem_init(4096, FIRST_FIT));

   int *data = (int *)mem_alloc(sizeof(int));
   assert(data != NULL);
   *data = DATA;
   assert(*data == DATA);

   exit(0);
}
