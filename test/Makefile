FILES := $(wildcard *.c)
TARGETS := ${FILES:.c=}

all: ${TARGETS}

%: %.c
	gcc -I../src -g -m64 -Xlinker -rpath=../src -o $@ $< -L../src -lmemory -std=gnu99

clean:
	rm -rf ${TARGETS} *.o
