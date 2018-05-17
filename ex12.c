#include <stdio.h>

int main(int argc, char *argv[])
{
        char full_name[] = {
            'Z', 'e', 'd', 
            ' ', 'A', '.', ' ',
            'S', 'h', 'a', 'W', '\0'
        };
        int areas[] = {10, 12, 13, 14, 20};
        char name[] = "Zed";

        //name[] = "ZedsDead";
        name[0] = 'B';
        areas[0] = 666;

        //WARNING: On some systems you may have to change the
        // %ld in this code to a %u since it will use unisgned ints
        printf("The size of an uninitialized int: %ld\n", sizeof(int));
        printf("The size of an initialized int: %ld\n", sizeof(101));
        printf("The size of areas: %ld\n", 
                sizeof(areas));
        printf("The number of ints in areas: %ld\n", 
                sizeof(areas) / sizeof(int));
        printf("The first area is %d, the second is %d.\n", 
                areas[0], areas[1]);
        
        printf("\nThe size of a char: %ld\n", sizeof(char));
        printf("The size of name (char[]): %ld\n", sizeof(name));
        printf("The number of chars: %ld\n", sizeof(name) / sizeof(char));        
        
        printf("\nThe size of full_name (char[]): %ld\n",
                sizeof(full_name));
        printf("the number of chars: %ld\n",
                sizeof(full_name) / sizeof(char));

        printf("name=\"%s\" and full_name=\"%s\"\n",
                name, full_name);
        
        return 0;
}
