rm *.o *.so ex29
cc -c libex29.c -o libex29.o
cc -shared -o libex29.so libex29.o
cc -Wall -g -DNDEBUG ex29.c -ldl -o ex29
./ex29 ./libex29.so lowercase  "hello THERE"
./ex29 ./libex29.so uppercase  "hello THERE"
