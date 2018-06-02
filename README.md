# learning_c_the_hard_way
Exercises for the amazing http://c.learncodethehardway.org/book/

Original code at `https://github.com/zedshaw/learn-c-the-hard-way-lectures`

## Basics

To run a compiled c  binary you just need the path so 

`./ex1`

## Useful Command line snippets

`make` is the standard way to build c programs but that expects a file called `makefile` to exist. You can run any makefile by 

```
make -f MyMakefile
```

## Makefiles

In a folder when running make it will look for the default make file name `Makefile`. So in this pproject root you could run 

`make Makefile clean` or `make clean` and they will do the same thing

It seems that one rule `all:` needs to be one line i.e.

```
all: ex3
```

## Debugging

The '-g' flag must be passed to make debugging work!

i.e below won't work 

`cc ./ex17.c -o ex17`

it needs to look like

`cc -Wall -g ./ex17.c -o ex17`

Use `lldb` on OSX or `gdb` on linux.The commands are quite similar. Example with lldb

```
lldb

$ target create ex1

# set a breakpoint at start of function name
$ b main  

# run through program
$ run

```
or 
```
run [args]
```

Then you can use c (continue), n (next) and s (step into) to continue, next and step through the program

You can also print out individual vars like

`print temp`

## Memory Allocation

## Heap

Permanent locations in the system memory which need to be allocated with `malloc` and deallocated with `free`, all of the rest of the system memory is potentially accesible by this.

## Stack

Is of a certain size and is used by temporary variables which are created within the scope of a function.
