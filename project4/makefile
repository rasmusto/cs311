CC=gcc
CFLAGS=-Wall -Wextra -g

BINS=myShell
OBJS=get_my_args.o do_command.o check_command.o
LIBS=libshell.a

default: build

build: ${BINS}
	rm -f dump
	tar -czf proj4.tar.gz myShell.h *.c makefile

#===================== BINS =======================

myShell: myShell.c libshell.a
	${CC} ${CFLAGS} -o myShell myShell.c libshell.a

#==================================================


#===================== OBJS =======================
${OBJS}: myShell.h
#==================================================


#===================== LIBS =======================
libshell.a: ${OBJS} myShell.h
	ar -r libshell.a ${OBJS}
#==================================================


###################### MISC #######################
clean:
	@echo "Cleaning up files..."
	rm -f ${BINS}
	rm -f ${OBJS}
	rm -f ${LIBS}
	rm -f dump
	@echo "Done."

run:
#	./myShell
