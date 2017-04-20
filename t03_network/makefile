VERSION	= 1.0
CC	= gcc
CFLAGS	= -Wall --pedantic -D_POSIX_C_SOURCE=200809L -g -D_REENTRANT -DVERSION=\"$(VERSION)\"
LDFLAGS	=

OBJSERVER	= server.o myhead.h
OBJCPROG	= program.o myhead.h
OBJCLIENT	= client.o myhead.h

all: server program client clean

server: $(OBJSERVER)
	$(CC) $(CFLAGS) $(OBJSERVER) $(LDFLAGS) -o server

moveserver:
	mv a.out server

program: $(OBJPROG)
	$(CC) $(CFLAGS) $(OBJPROG) $(LDFLAGS) -o program

moveprogram:
	mv a.out program

client: $(OBJCLIENT)
	$(CC) $(CFLAGS) $(OBJCLIENT) $(LDFLAGS) -o client

moveclient:
	mv a.out client

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm server.o program.o client.o
