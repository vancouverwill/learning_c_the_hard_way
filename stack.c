//#define NDEBUG 0
#include "dbg.h"
#include <stdio.h>
#include <stdlib.h>


struct Node {
    struct Node *next;
    char *varchar;
};

struct Stack {
    struct Node *first;
    int size;
};

void initialize(struct Stack *stack) 
{
	stack->size = 0;
}

void push(struct Stack *stack, char *varchar) 
{

    struct Node *oldFirst = stack->first;
    
    stack->size++;

    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->varchar = varchar;
    newNode->next = oldFirst;


    stack->first = newNode;
}

char *pop(struct Stack *stack)
{
if (stack->size <= 0) {
	return "";
}
  char *firstItem = stack->first->varchar;
  struct Node *firstNode = stack->first;
  stack->first = stack->first->next;
  free(firstNode);
  stack->size--;
  
  return firstItem;
}

void stack_close(struct Stack *stack)
{
	debug("start stack close");
    if (stack) {
		debug("stack_close: stack exists");
        if (stack->first) { 
			debug("stack_close: stack first exists");
            //struct Node *currentNode = stack->first;
            //while(stack->first && stack->first->varchar){
			while(stack->size > 0) {
			debug("stack_close: inside while");
			debug("cleaning out %s", stack->first->varchar);
                struct Node *firstNode = stack->first;
         //       struct Node *oldNode = currentNode;
                stack->first =  stack->first->next;
           //     free(oldNode);
                free(firstNode);
			debug("end of while loop %p", stack->first );
			stack->size--;
            }
			debug("stack first is now null");
			//free(currentNode);
            //free(stack->first);
        }

        //if (stack->size) free(stack->size);
	//	free(stack->size);
     //   free(stack);
    }
	debug("outside of main loop");
}

int main(int argc, char *argv[])
{
   	//printf("main debug:%d", NDEBUG); 
	struct Stack *stack = malloc(sizeof(struct Stack)); 
    debug("main"); 
    push(stack, "wiliam");
    push(stack, "james");
    push(stack, "jim");
    push(stack, "jake");
/*    push(stack, "jill");
    push(stack, "trump");
    push(stack, "mike");
    push(stack, "matt");
  */

	debug("finishing pushing");
    printf("%s\n", pop(stack));
    printf("%s\n", pop(stack));
    //printf("%s\n", pop(stack));
    //printf("%s\n", pop(stack));
    //printf("%s\n", pop(stack));
	debug("finishing poping");
    
	debug("attempt to call stack close");
    stack_close(stack);
	free(stack);
	debug("finished");
    return 0;
}
