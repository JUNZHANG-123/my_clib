.SUFFIXES: .c .o                             
INC = -Iinc
LIB =
SRC = *.c ./src/*.c
CC = cc
CC_FLAG = -g -c -Os -Wall -Tscript.lds

TARGET = my_test
OBJECTS = $(patsubst %.c,%.o,$(wildcard $(SRC)))
$(TARGET):$(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(INC) -Tscript.lds $(LIB) 
.c.o:
	$(CC) $(CC_FLAG) $(INC) -o $@ $<
.PRONY:clean
clean:
	-rm -f $(OBJECTS) $(TARGET)