# CFLAGS sets the environmental variables
#  Wall to show all error flagsdd and -g to put in debugging mode
CFLAGS="-Wall -g"

all: ./ex1.c
#	./ex1.c ./ex3.c

clean:
	rm -f ex1 ex3 ex4 ex5 ex6 ex7 ex8 ex9 ex10 ex11 ex12 ex13 ex14 ex15

random:
	echo 'hello world;'
