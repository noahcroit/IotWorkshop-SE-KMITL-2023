#make file - Redis Subscribe example
 
CC=gcc  #compiler
#target file name (output bin)
TARGET=redis_sub
 
all:
	$(CC) redis-subscribe.c -l hiredis -l event -o $(TARGET)
clean:
	rm $(TARGET)
