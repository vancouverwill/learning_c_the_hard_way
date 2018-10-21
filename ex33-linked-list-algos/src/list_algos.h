#ifndef lcthw_List_algos_h
#define lcthw_List_algos_h

#include <lcthw/list.h>
#include <sys/time.h>

typedef int (*List_compare) (const void *a, const void *b);

int List_bubble_sort(List * list, List_compare cmp);

int List_bubble_sort_optimized(List * list, List_compare cmp);

List *List_merge_sort(List * list, List_compare cmp);

/**
 * Returns the current time in microseconds.
 */
long get_micro_time(){
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);
    return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

#endif
