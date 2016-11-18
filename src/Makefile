main: hashtable.o
	gcc  -g -c -o main.o -O3 main.c
	gcc  -o test -O3 ht.o main.o

hashtable.o:
	gcc  -g -o ht.o -c  -O3  hashtable.c


clean:
	
	if [ -f test ]; then rm test; fi
	rm *.o 

