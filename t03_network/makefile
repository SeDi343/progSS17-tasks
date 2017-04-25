VERSION	= 1.0
CC	= clang
CFLAGS	= -Wall --pedantic -D_POSIX_C_SOURCE=200809L -g -D_REENTRANT -DVERSION=\"$(VERSION)\"
LDFLAGS	=

OBJSERVER	= server.o
OBJCPROG	= serverprogram.o
OBJCLIENT	= client.o

all: server client program clean

server: $(OBJSERVER)
	$(CC) $(CFLAGS) $(OBJSERVER) $(LDFLAGS)
	mv a.out server

program: $(OBJCPROG)
	$(CC) $(CFLAGS) $(OBJCPROG) $(LDFLAGS)
	mv a.out serverprogram

client: $(OBJCLIENT)
	$(CC) $(CFLAGS) $(OBJCLIENT) $(LDFLAGS)
	mv a.out client

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	find . -name "*.o" -exec rm {} \;
	find . -name "*.h.gch" -exec rm {} \;
