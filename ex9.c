#include <stdio.h>

int main(int argc, char *argv[])
{
    int numbers[4] = {'e'};
    char name[4] = {'a','a','a'};

    name[3] = '\0';

    // first, print them out raw
    printf("numbers: %d %d %d %d\n",
            numbers[0], numbers[1],
            numbers[2], numbers[3]);

    printf("name each: %c %c %c %c\n",
            name[0], name[1],
            name[2], name[3]);

    printf("name : %s\n", name);

    //setup the numbers
    numbers[0] = 1;
    numbers[1] = 'e';
    numbers[2] = 'g';
    numbers[3] = 4;

    // setup the name
    name[0] = 100;
    name[1] = 'e';
    name[2] = 'd';
    name[3] = '\0';

    // then print them out intialized
    printf("numbers: %d %d %d %d\n",
            numbers[0], numbers[1],
            numbers[2], numbers[3]);

    printf("name each: %c %c %c %c\n",
            name[0], name[1],
            name[2], name[3]);

    printf("name as ints each: %d %d %d %d\n",
            name[0], name[1],
            name[2], name[3]);

    //print the name like a string
    printf("name : %s\n", name);

    //another way to use name
    char *another = "Zed";

    printf("another: %s\n", another);

    printf("another each: %c %c %c %c\n",
            another[0], another[1],
            another[2], another[3]);

    return 0;
}

