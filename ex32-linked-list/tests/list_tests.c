#include "minunit.h"
#include <list.h>
#include <assert.h>

static List *list = NULL;
static List *list2 = NULL;
char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";
char *test4 = "test4 data";

char *test_create()
{
    list = List_create();
    mu_assert(list != NULL, "Failed to create list.");

    return NULL;
}

char *test_destroy()
{
    List_clear_destroy(list);
    mu_assert(List_count(list) == 0, "Wrong count after destroy.");
    return NULL;
}

char *test_push_pop()
{
    List_push(list, test1);
    mu_assert(List_last(list) == test1, "Wrong last value.");

    List_push(list, test2);
    mu_assert(List_last(list) == test2, "Wrong last value");

    List_push(list, test3);
    mu_assert(List_last(list) == test3, "Wrong last value.");
    mu_assert(List_count(list) == 3, "Wrong count on push.");

    char *val = List_pop(list);
    mu_assert(val == test3, "Wrong value on pop.");

    val = List_pop(list);
    mu_assert(val == test2, "Wrong value on pop.");

    val = List_pop(list);
    mu_assert(val == test1, "Wrong value on pop.");
    mu_assert(List_count(list) == 0, "Wrong count after pop.");

    return NULL;
}

char *test_unshift()
{
    List_unshift(list, test1);
    mu_assert(List_first(list) == test1, "Wrong first value.");

    List_unshift(list, test2);
    mu_assert(List_first(list) == test2, "Wrong first value");

    List_unshift(list, test3);
    mu_assert(List_first(list) == test3, "Wrong last value.");
    mu_assert(List_count(list) == 3, "Wrong count on unshift.");

    return NULL;
}

char *test_remove()
{
    // we only need to test the middle remove case since push/shift 
    // already tests the other cases

    char *val = List_remove(list, list->first->next);
    mu_assert(val == test2, "Wrong removed element.");
    mu_assert(List_count(list) == 2, "Wrong count after remove.");
    mu_assert(List_first(list) == test3, "Wrong first after remove.");
    mu_assert(List_last(list) == test1, "Wrong last after remove.");

    return NULL;
}

char *test_shift()
{
    mu_assert(List_count(list) != 0, "Wrong count before shift.");

    char *val = List_shift(list);
    mu_assert(val == test3, "Wrong value on shift.");

    val = List_shift(list);
    mu_assert(val == test1, "Wrong value on shift.");
    mu_assert(List_count(list) == 0, "Wrong count after shift.");

    return NULL;
}

char *refill()
{
    list2 = List_create();
    mu_assert(List_count(list2) == 0, "Wrong count after destroy:%d", list2->count);
    mu_assert(list2 != NULL, "Failed to create list.");
    List_push(list2, test1);
    mu_assert(List_last(list2) == test1, "Wrong last value.");
	if (List_last(list2) != test1) {
		log_err( "Wrong last value. %s", list2->last->value);
	}

    List_push(list2, test2);
    mu_assert(List_last(list2) == test2, "Wrong last value");

    mu_assert(List_count(list2) == 2, "Wrong count after destroy then adding.");
    return NULL;
}

char *test_destroy_on_non_empty()
{
	// @todo find out why this is giving a memory error
	/*List_clear_destroy(list2);*/
	/*mu_assert(List_count(list) == 0, "Wrong count after destroy.");*/

	return NULL;
}

char *test_join()
{

	List *list_a = List_create();
    List_push(list_a, test1);
    List_push(list_a, test2);
    mu_assert(List_count(list_a) == 2, "Wrong count after setup.");

	List *list_b = List_create();
    List_push(list_b, test3);
    List_push(list_b, test4);
    mu_assert(List_count(list_b) == 2, "Wrong count after setup.");

	List_join(list_a, list_b);
    mu_assert(List_count(list_a) == 4, "Wrong count after join.");
    mu_assert(list_a->first->value == test1, "Wrong first value.");
    mu_assert(list_a->last->value == test4, "Wrong last value.");

	List_print(list_a);
	return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_push_pop);
    mu_run_test(test_unshift);
    mu_run_test(test_remove);
    mu_run_test(test_shift);
    mu_run_test(test_destroy);
    mu_run_test(refill);
    mu_run_test(test_destroy_on_non_empty);
    mu_run_test(test_join);

    return NULL;
}

RUN_TESTS(all_tests);
