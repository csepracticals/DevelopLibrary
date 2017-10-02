TARGET:liblist.a exe
liblist.a:LinkedListApi.o
	ar rs liblist.a LinkedListApi.o
exe:main.o liblist.a
	gcc -g main.o -o exe -L . -llist
LinkedListApi.o:LinkedListApi.c
	gcc -g -c -I . LinkedListApi.c -o LinkedListApi.o
main.o:main.c
	gcc -g -c -I . main.c -o main.o
clean:
	rm *.o
	rm exe
	rm liblist.a
