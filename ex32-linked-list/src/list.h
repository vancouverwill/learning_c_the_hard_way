#ifndef lcthw_List_h
#define lcthw_List_h

#include <stdlib.h>

struct ListNode;
typedef struct ListNode
{
	struct ListNode *next;
	struct ListNode *prev;
	void *value;
} ListNode;

typedef struct List
{
	int count;
	ListNode *first;
	ListNode *last;
} List;

List *List_create();
void List_destroy(List *list);
void List_clear(List *list);
void List_clear_destroy(List *list);

#define List_count(A) ((A)->count)
#define List_first(A) ((A)->first != NULL ? (A)->first->value : NULL)
#define List_last(A) ((A)->last != NULL ? (A)->last->value : NULL) 

// adds a new element to the end
void List_push(List *list, void *value);
// get the last element
void *List_pop(List *list);

// adds a new element to the front
void List_unshift(List *list, void *value);
// removes the front element:
void *List_shift(List *list);

// removes a specific item from the list
void *List_remove(List *list, ListNode *node);

// backslash is the line continuation character allowing us to write a long line in multiple lines
/* These preprocessor directives extend only across a single line of code. As soon as a newline character is found, the preprocessor directive is ends. No semicolon (;) is expected at the end of a preprocessor directive. The only way a preprocessor directive can extend through more than one line is by preceding the newline character at the end of the line by a backslash (\). */
#define LIST_FOREACH(L, S, N, V) ListNode *_node = NULL;\
											ListNode *V = NULL;\
for (V = _node = L->S; _node != NULL; V = _node = _node->N)

#endif
