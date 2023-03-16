#make file - Redis Set&Get example
 
CC=gcc  #compiler
#target file name (output bin)
TARGET=redis_set
 
all:
	$(CC) redis-set.c -l hiredis -o $(TARGET)
clean:
	rm $(TARGET)
