#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
// include testing class when built

#define STARTING_SET_SIZE 10

#define TST_P "test successful:"
#define TST_F "test failed:"


struct Set {
    int count;
    int capacity;
    int data[STARTING_SET_SIZE];
};

void testTrue(bool expected, char *message);

struct Set *constructSet()
{
    struct Set *set = malloc(sizeof(int) * 2 + STARTING_SET_SIZE * sizeof(int));
    set->count = 0;
    set->capacity = STARTING_SET_SIZE;
    return set;
}


void SetClose(struct Set *set)
{
    free(set);
}

void die(const char *message, struct Set *set)
{
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }
    SetClose(set);
    exit(1);
}

bool empty(struct Set *set)
{
    return set->count == 0;
}

bool full(struct Set *set)
{
    return  set->count == set->capacity;
}

void grow(struct Set *set)
{
   set->capacity = set->capacity * 2;
   
   set = realloc(set, sizeof(int) * 2 + set->capacity * sizeof(int));
    
   /*int i;
   for (i = 0; i < set->count; i++) {
       newSet->data[i] = set->data[i];
   }*/
   //newSet->count = set->count;
   
   //set = newSet;
}

void shrink(struct Set *set)
{
    set->capacity = set->capacity / 2;
    set = realloc(set, sizeof(int) * 2 + set->capacity * sizeof(int));
}

void add(struct Set *set, int input)
{
    if (full(set)) grow(set);
    int previousCount = set->count; 
    //printf("add1 - %d %d \n", input, set->count);
    set->data[set->count] = input;    
    //*(set->data + 1) = input;    
    if (previousCount != set->count) {
        printf("add input :%d previouscount:%d nowCount%d \n", input, previousCount, set->count);
        
        printf("add input :%d set->data:%p set->data%p \n", input, &set->data, &set->count);
        
    }
    set->count += 1;
    //printf("add2 %d\n", set->count);
}

void rm(struct Set *set, int input)
{
    if (set->count < set->capacity / 2) shrink(set); 

    int i;
    for(i = 0; i < STARTING_SET_SIZE; i++) {
        if (set->data[i] != input) continue;
        set->data[i] = set->data[set->count];
        set->data[set->count] = -1;
        set->count--;
        return;
    }
}

int size(struct Set *set)
{
    return set->count;
}


void testEmpty()
{ 
    struct Set *set = constructSet();
    
    testTrue(empty(set) == true, "New set is empty");
    add(set, 123);

    testTrue(empty(set) == false, "Non empty set is not empty");

    SetClose(set);
}

void testSize()
{
    struct Set *set = constructSet();

    testTrue(size(set) == 0,  "New set is size 0");

    add(set, 1);
    testTrue(size(set) == 1,  "New set add one is size 1");

    rm(set, 1);
    testTrue(size(set) == 0,  "Old set rm one is size 0");

    SetClose(set);
}

void testFullAndGrow()
{
    struct Set *set = constructSet();
    int i = 0;

    for (i = 0; i < STARTING_SET_SIZE * 3; i++) {
        add(set, i);
    }

    printf("%i %i %i\n", full(set), set->capacity, set->count);
    
    testTrue(set->count == 30, "added 30 elements");
    
    //rm(set, 29);
    for (i = 0; i < STARTING_SET_SIZE * 3; i++) {
        rm(set, i);
    }
    printf("%i %i %i\n", full(set), set->capacity, set->count);
    
    testTrue(set->count == 0, "removed 30 elements");
    
    SetClose(set);
}

void testTrue(bool expected, char *message)
{
if (expected == true) {
        printf("%s %s\n", TST_P, message);
    } else {
        printf("%s %s\n", TST_F, message);
    }
}

void runTests(struct Set *set)
{
    testEmpty();
    testSize();
    testFullAndGrow();
}

int main(int argc, char *argv[])
{
    struct Set *set = constructSet();
    
    runTests(set);
    SetClose(set);     
    return 0;
}
