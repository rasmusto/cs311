CC=gcc
CFLAGS=-Wall -Wextra -g

BINS=client server

default: build

build: ${BINS}

#===================== BINS =======================

client: client.c
	${CC} ${CFLAGS} -o client client.c

server: server.c server.h
	${CC} ${CFLAGS} -o server server.c

#==================================================


###################### MISC #######################
clean:
	@echo "Cleaning up files..."
	rm -f ${BINS}
	@echo "Done."

s:
	./server 8001

c:
	./client 127.0.0.1 8001
