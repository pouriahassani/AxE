OBJ = main.o fftmisc.o  fourierf.o util.o
FILE = main.c fftmisc.c  fourierf.c util.c
CFLAGS =  -g

fft: ${OBJ} Makefile
	gcc  ${CFLAGS} ${OBJ} -o fft 
fftmisc.o: fftmisc.c
	gcc ${CFLAGS} -c fftmisc.c
fourierf.o: fourierf.c
	gcc ${CFLAGS} -c fourierf.c
main.o: main.c
	gcc ${CFLAGS} -c main.c

util.o: util.c
	gcc ${CFLAGS} -c util.c

clean:
	rm -rf *.o fft output*