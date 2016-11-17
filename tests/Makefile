main: hashtable.o unit.o
	gcc  -fno-builtin-printf -c -o example.o -O3 example.c
	gcc  -o test -O3 ht.o unit.o example.o

hashtable.o:
	gcc  -o ht.o -c  -O3  ../src/hashtable.c

unit.o:
	gcc  -o unit.o -c  -O3  unit.c



clean:
	
	if [ -f test ]; then rm test; fi
	rm *.o 

