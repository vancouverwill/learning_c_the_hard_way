CFLAGS=-Wall -g -DBDEBUG

ex22.o: ./ex22.c

ex22_main: ./ex22_main.c ./ex22.o
	cc -Wall -g -DBDEBUG ex22_main.c ex22.o -o ex22_main

combine: ex22.o ex22_main

echo:
	@echo	./ex22.c -o ./ex22.0 	
	@echo	ex22_main.c ex22.o -o ex22m_main
