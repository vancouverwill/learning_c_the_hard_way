#include <stdio.h>
#include <ctype.h>
#include <string.h>

// forward declarations
int can_print_it(char ch);
void print_letters(char arg[]);
void handle_arguments(int count, char *command_line_args[]);

void print_arguments(int argc, char *argv[])
{
    
    handle_arguments(argc, argv);
    
    /*int i = 0;

    for(i = 0; i < argc; i++) {
        print_letters(argv[i]);
        printf("use pointers to access array \n");
        print_letters(*(argv+i));
    }*/
}


void handle_arguments(int count, char *command_line_args[])
{
    int i = 0;

    for(i = 0; i < count; i++) {
        print_letters(command_line_args[i]);
        printf("use pointers to access array \n");
        print_letters(*(command_line_args+i));
        printf("\n");
        printf("\n");
    }
}
void print_letters(char arg[])
{
    int i = 0;

    for(i = 0; arg[i] != '\0'; i++) {
        char ch = arg[i];

        if(can_print_it(ch)) {
            printf("'%c' == %d ", ch, ch);
        }
    }

    printf("\n");

    for (i = 0; i < strlen(arg); i++) {
        char ch = arg[i];

        if(can_print_it(ch)) {
            printf("'%c' == %d ", ch, ch);
        }
    }
                
    printf("\n");
}
int can_print_it(char ch)
{
    return isalpha(ch) || isblank(ch);
}

int main(int argc, char *argv[])
{
    print_arguments(argc, argv);
    return 0;
}
