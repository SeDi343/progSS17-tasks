VERSION	= 1.0
CC	= gcc
CFLAGS	= -Wall --pedantic -D_POSIX_C_SOURCE=200809L -g -D_REENTRANT -DVERSION=\"$(VERSION)\"
LDFLAGS	=

OBJSERVER = server.o myhead.h
OBJCLIENT = program.o myhead.h

all: server moveserver program moveprogram clean

server: $(OBJSERVER)
	$(CC) $(CFLAGS) $(OBJSERVER) $(LDFLAGS)

moveserver:
	mv a.out server

program: $(OBJCLIENT)
	$(CC) $(CFLAGS) $(OBJCLIENT) $(LDFLAGS)

moveprogram:
	mv a.out program

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm server.o program.o
