.PHONY: clean all

all : get put

get: get.o shmfifo.o
	gcc $^ -o $@

put : put.o shmfifo.o
	gcc $^ -o $@

%.o : %.c
	gcc -c $^ -o $@

clean:
	rm -rf *.o get put
