LIBNAME=libglthread.a
TARGET:${LIBNAME} exe
${LIBNAME}:glthread.o
	ar rs ${LIBNAME} glthread.o
exe:main.o ${LIBNAME}
	gcc -g main.o -o exe -L . -lglthread
glthread.o:glthread.c
	gcc -g -c -I . glthread.c -o glthread.o
main.o:main.c
	gcc -g -c -I . main.c -o main.o
clean:
	rm *.o
	rm exe
	rm ${LIBNAME}
