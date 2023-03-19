PROG = main
CC = gcc
CFLAGS = `pkg-config --cflags gtk4`
LIBS = `pkg-config --libs gtk4`

${PROG}: ${PROG}.c 
	${CC} ${CFLAGS} -o ${PROG} ${PROG}.c ${LIBS}

clean:
	rm ${PROG}
