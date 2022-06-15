mem: memory.c memory.h
	gcc -g -c -Wall -m64 -fpic memory.c -O
	gcc -g -shared -Wall -m64 -o libmemory.so memory.o -O

clean:
	rm -rf memory.o libmemory.so
