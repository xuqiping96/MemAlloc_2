#include <assert.h>
#include <stdlib.h>

#include "memory.h"

int main()
{
  assert(!mem_init(4096, FIRST_FIT));

  void *data[9];
  void *test;

  data[0] = mem_alloc(300);
  assert(data[0]);

  data[1] = mem_alloc(200);
  assert(data[1]);

  data[2] = mem_alloc(200);
  assert(data[2]);

  data[3] = mem_alloc(100);
  assert(data[3]);

  data[4] = mem_alloc(200);
  assert(data[4]);

  data[5] = mem_alloc(800);
  assert(data[5]);

  data[6] = mem_alloc(500);
  assert(data[6]);

  data[7] = mem_alloc(700);
  assert(data[7]);

  data[8] = mem_alloc(300);
  assert(data[8]);

  assert(!mem_free(data[1]));
  assert(!mem_free(data[3]));
  assert(!mem_free(data[5]));
  assert(!mem_free(data[7]));

  test = mem_alloc(50);

  assert(
      (((unsigned long int)test >= (unsigned long int)data[1]) &&
       ((unsigned long int)test < (unsigned long int)data[2])) ||
      (((unsigned long int)test <= (unsigned long int)data[8])));
  exit(0);
}
