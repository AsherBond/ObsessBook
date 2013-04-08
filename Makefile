CC = gcc
CFLAGS = -Wall -g

all: obook

user.o: user.c user.h
	$(CC) $(CFLAGS) -c user.c

userdb.o: userdb.c userdb.h user.h
	$(CC) $(CFLAGS) -c userdb.c

derpcon.o: derpcon.h user.h derpcon.c
	$(CC) $(CFLAGS) -c derpcon.c

obook: main.c user.o userdb.o derpcon.o
	$(CC) $(CFLAGS) main.c user.o userdb.o derpcon.o -o $@

clean:
	rm -f obook *.o

