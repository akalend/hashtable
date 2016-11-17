main: hashtable.o unit.o
	gcc  -g -c -o test.o -O3 test.c
	gcc  -o test -O3 ht.o unit.o test.o

hashtable.o:
	gcc -g -o ht.o -c  -O3  ../src/hashtable.c

unit.o:
	gcc  -o unit.o -c -std=c99 -O3  unit.c



clean:
	
	if [ -f test ]; then rm test; fi
	rm *.o 

