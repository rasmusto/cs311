CC=gcc
CFLAGS=-Wall -Wextra -g

BINS=createPict growTree putPerson buildHouse showTrees showPeople showHouses showAll remove
OBJS=drawTree.o drawPerson.o drawHouse.o userMv.o showTrees.o showPeople.o showHouses.o show.o lockfile.o
LIBS=libdraw.a

default: build

build: ${BINS}
	if test -e .draw_config; then rm .draw_config; fi
	touch .draw_config
	if test -e fileLog; then rm fileLog; fi
	if test -e fileLog2; then rm fileLog2; fi
	rm -f *.LCK
	rm -f .draw_config.LCK
	#cp all.bak all

#===================== BINS =======================

createPict: picture.h createPict.c libdraw.a
	${CC} ${CFLAGS} -o createPict createPict.c libdraw.a

growTree: picture.h growTree.c libdraw.a
	${CC} ${CFLAGS} -o growTree growTree.c libdraw.a -lncurses

putPerson: picture.h putPerson.c libdraw.a
	${CC} ${CFLAGS} -o putPerson putPerson.c libdraw.a -lncurses

buildHouse: picture.h buildHouse.c libdraw.a
	${CC} ${CFLAGS} -o buildHouse buildHouse.c libdraw.a -lncurses


showAll: picture.h showAll.c showHouses showPeople showTrees libdraw.a
	${CC} ${CFLAGS} -o showAll showAll.c libdraw.a -lncurses

showHouses: picture.h showHouses.c libdraw.a
	${CC} ${CFLAGS} -o showHouses showHouses.c libdraw.a -lncurses

showPeople: picture.h showPeople.c libdraw.a
	${CC} ${CFLAGS} -o showPeople showPeople.c libdraw.a -lncurses

showTrees: picture.h showTrees.c libdraw.a
	${CC} ${CFLAGS} -o showTrees showTrees.c libdraw.a -lncurses


remove: picture.h remove.c libdraw.a
	${CC} ${CFLAGS} -o remove remove.c libdraw.a -lncurses

#==================================================


#===================== OBJS =======================
${OBJS}: picture.h
#==================================================


#===================== LIBS =======================
libdraw.a: ${OBJS} picture.h
	ar -r libdraw.a ${OBJS}
#==================================================


###################### MISC #######################
clean:
	@echo "Cleaning up files..."
	rm -f ${BINS}
	rm -f ${OBJS}
	rm -f ${LIBS}
	if test -e .draw_config; then rm .draw_config; fi
	@echo "Done."
run:
	@echo "Writing test to fileLog1..."
	./check.sh all
	@echo "Done."
diff:
	vimdiff fileLog1 fileLog2
