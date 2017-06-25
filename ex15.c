#include <stdio.h>


void print_names_and_ages(int ages[], char *names[], int ages_count) {
    int i = 0;
   
    printf("--- print_names_and_ages() count:%d\n", ages_count);

    // first way using indexing
    printf("first way using indexing");
            
    for (i = 0; i < ages_count; i++) {
        printf("ARRAYS %s has %d years alive.\n",
                names[i], 
                ages[i]);
        printf("POINTERS %s:%i has %d years alive.\n",
                *(names+i), **(names+i), *(ages+i));
        printf("ADDRESSES %p has %d years alive.\n",
                &names[i], ages[i]);
    }
    printf("---\n");
}


void print_names_and_ages_with_pointers(int ages[], char *names[], int ages_count) {
    //setup the pointers to the start of the arrays
    int i;
    int *cur_age = ages;
    char **cur_name = names;

    // second way using pointers
    for(i = 0; i < ages_count; i++) {
        printf("%s is %d years old.\n",
                *(cur_name+i), *(cur_age+i));
    }

    printf("---REVERSE\n");
    
    for(i = ages_count - 1; i >= 0; i--) {
        printf("%s is %d years old.\n",
                *(cur_name+i), *(cur_age+i));
    }

    printf("---\n");
}    


void print_names_and_ages_with_pointers_used_as_arrays(int ages[], char *names[], int ages_count) {
    //third way, pointers are just arrays
    int i;
    int *cur_age = ages;
    char **cur_name = names;

    for(i = 0; i < ages_count; i++) {
        printf("%s is %d years old again.\n",
                cur_name[i], cur_age[i]);
    }

    printf("---\n");
}


void print_names_and_ages_with_pointers_used_in_stupid_complex_way(int ages[], char *names[], int ages_count) {
    // fourth way with pointers in a stupid complex way
    int *cur_age = ages;
    char **cur_name = names;

    for(cur_name = names, cur_age = ages;
            (cur_age - ages) < ages_count;
            cur_name++, cur_age++)
    {
        printf("%s lived %d years so far.\n",
                *cur_name, *cur_age);
        printf("Using pointers to access array index. %s lived %d years so far.\n",
                names[cur_age-ages], ages[cur_age-ages]);
    }
    printf("%i", *(ages+1));
 
    printf("--- REVERSE\n");
    
    // fourth way reverse with pointers in a stupid complex way
    for(cur_name = names + ages_count - 1, cur_age = ages + ages_count - 1;
            (cur_age - ages) >= 0;
            cur_name--, cur_age--)
    {
        printf("%s lived %d years so far.\n",
                *cur_name, *cur_age);
    }
    printf("%i", *(ages+1));

}


int main(int argc, char *argv[])
{
    // create two arrays we care about
    int ages[] = {23, 43, 12, 89, 2};
    char *names[] = {
        "Alan", "Frank", 
        "Mary", "John", "Lisa"
    };

    // safely get the size of ages, count needs to be calculated here and cannot be refactored to a function because when an array is passed as a pointer, a pointer knows the address where the array starts but it doesn't know it's size
    int count = sizeof(ages) / sizeof(int);

    print_names_and_ages(ages, names, count);
    
    print_names_and_ages_with_pointers(ages, names, count);
    
    print_names_and_ages_with_pointers_used_as_arrays(ages, names, count);
    
    print_names_and_ages_with_pointers_used_in_stupid_complex_way(ages, names, count);
    
    
    //cur_age = (int)&names;

    return 0;
}


