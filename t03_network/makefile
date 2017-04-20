VERSION	= 1.0
CC	= gcc
CFLAGS	= -Wall --pedantic -D_POSIX_C_SOURCE=200809L -g -D_REENTRANT -DVERSION=\"$(VERSION)\"
LDFLAGS	=

OBJSERVER	= server.o myhead.h
OBJCPROG	= program.o myhead.h
OBJCLIENT	= client.o myhead.h

all: server client program clean


server: $(OBJSERVER)
	$(CC) $(CFLAGS) $(OBJSERVER) $(LDFLAGS)
	mv a.out server

program: $(OBJPROG)
	$(CC) $(CFLAGS) $(OBJPROG) $(LDFLAGS)
	mv a.out program

client: $(OBJCLIENT)
	$(CC) $(CFLAGS) $(OBJCLIENT) $(LDFLAGS)
	mv a.out client

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	find . -name "*.o" -exec rm {} \;
	find . -name "*.h.gch" -exec rm {} \;
