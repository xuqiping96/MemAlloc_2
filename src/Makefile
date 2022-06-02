mem: memory.c memory.h
	gcc -g -c -Wall -m32 -fpic memory.c -O
	gcc -g -shared -Wall -m32 -o libmemory.so memory.o -O

clean:
	rm -rf memory.o libmemory.so
