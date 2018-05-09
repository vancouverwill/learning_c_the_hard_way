# learning_c_the_hard_way
Exercises for the amazing http://c.learncodethehardway.org/book/

## Basics

To run a compiled c  binary you just need the path so 

`./ex1`

## Useful Command line snippets

`make` is the standard way to build c programs but that expects a file called `makefile` to exist. You can run any makefile by 

```
make -f MyMakefile
```

## Debugging

Use `lldb` on OSX or `gdb` on linux. The commands are quite similar. Example with lldb

```
lldb

$ target create ex1

# set a breakpoint at start of function name
$ b main  

# run through program
$ run

```

Then you can use c, n and s to continue, next and step through the program


