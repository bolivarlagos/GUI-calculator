PROG = main
CC = gcc
CFLAGS = `pkg-config --cflags gtk4`
LIBS = `pkg-config --libs gtk4`
# CFLAGS = `pkg-config --cflags gtk+-3.0`
# LIBS = `pkg-config --libs gtk+-3.0`

${PROG}: ${PROG}.c 
	${CC} ${CFLAGS} -o ${PROG}.o ${PROG}.c ${LIBS}

clean:
	rm ${PROG}.o
