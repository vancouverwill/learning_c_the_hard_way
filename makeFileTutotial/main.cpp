#include <iostream>
#include "functions.h"

int main(int argc, char *argv[]){
    if ( argc != 2 ) /* argc should be 2 for correct execution */
    {
        /* We print argv[0] assuming it is the program name */
        std::cout << std::endl;
        printf( "usage: %s 50", argv[0] );
        std::cout << std::endl;
        std::cout << std::endl;
        return 0;
    }
    print_hello();
    std::cout << std::endl;
    std::cout << "The factorial of " << argv[1] << " is " << factorial(atoi(argv[1])) << std::endl;
    return 0;
}
