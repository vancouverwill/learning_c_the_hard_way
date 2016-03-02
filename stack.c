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

    //stack->root = null;
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
  char *firstItem = stack->first->varchar;
  struct Node *firstNode = stack->first;
  stack->first = stack->first->next;
  free(firstNode);
  stack->size--;

  return firstItem;
}

void stack_close(struct Stack *stack)
{
    if (stack) {
        if (stack->first) { 
            struct Node *currentNode = stack->first;
            while(currentNode->next){
                struct Node *nextNode = currentNode->next;
                struct Node *oldNode = currentNode;
                currentNode = nextNode;
                free(oldNode);
            }
            //free(stack->first);
        }
        //if (stack->size) free(stack->size);
        free(stack);
    }
}

int main(int argc, char *argv[])
{
    struct Stack *stack = malloc(sizeof(struct Stack)); 
    
    push(stack, "wiliam");
    push(stack, "james");
    push(stack, "jim");
    push(stack, "jake");
    push(stack, "jill");
    push(stack, "trump");
    push(stack, "mike");
    push(stack, "matt");
  
    printf("%s\n", pop(stack));
    printf("%s\n", pop(stack));
    

    stack_close(stack);
    return 0;
}
