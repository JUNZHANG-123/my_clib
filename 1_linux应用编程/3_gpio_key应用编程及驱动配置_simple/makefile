.SUFFIXES: .c .o                             
INC = -Iinc
LIB = -lpthread
SRC = *.c ./src/*.c
CC = cc
CC_FLAG = -g -c -Os -Wall
TARGET = my_test
OBJECTS = $(patsubst %.c,%.o,$(wildcard $(SRC)))
$(TARGET):$(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(INC) $(LIB)
.c.o:
	$(CC) $(CC_FLAG) $(INC) -o $@ $<
.PRONY:clean
clean:
	-rm -f $(OBJECTS) $(TARGET)