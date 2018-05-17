#include <stdio.h>

int main(int argc, char *argv[])
{
    // go through each string in argv
    
    int i = 0;
    while(i < argc) {
        printf("arg %d in order: %s\n", i, argv[i]);
        i++;
    }

    i = argc - 1;
    while(i >= 0) {
        printf("arg %d in reverse order: %s\n", i, argv[i]);
        i--;
    }

    //let's make our own aray of strings

    char *states[] = {
        "California", "Oregon", "Washington", "Texas", NULL
    };

    int num_states = 5;
    i = 0;
    while(i < num_states) {
        printf("state %d: %s\n", i, states[i]);
        i++;
    }
    
    i = 0;
    while(i < argc) {
        states[i] = argv[i];
        printf("states taken from args %d: %s\n", i, states[i]);
        i++;
    }

    return 0;
}
