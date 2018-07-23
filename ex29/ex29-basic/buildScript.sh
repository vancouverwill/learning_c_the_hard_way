rm *.o *.so  ex29
rm -rf *.dSYM
# compile the lib file (*.o) 
cc -c libex29-format-case.c -o libex29-format-case.o
# make the .so
cc -shared -o libex29-format-case.so libex29-format-case.o

# make the loader program
cc -Wall -g -DNDEBUG ex29-runner.c -ldl -o ex29-runner

#run the program
./ex29-runner ./libex29-format-case.so lowercase  "hello THERE"
./ex29-runner ./libex29-format-case.so uppercase  "hello THERE"
