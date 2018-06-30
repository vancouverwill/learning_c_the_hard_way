#include "dbg.h"
#include <time.h>
#include <stdio.h>
#include <string.h>

int normal_copy(char* from, char* to, int count)
{
    int i = 0;

    for (i = 0; i < count; i++) {
	to[i] = from[i];
    }

    return i;
}


int duffs_device(char* from, char* to, int count)
{
	debug("start duffs_device \nfrom:%s \nto:%s \ncount:%d", from, to, count); 
    {
	int n = (count + 7) / 8;

	switch (count % 8) {
	case 0:
	    do {
		*to++ = *from++;
	    case 7:
		*to++ = *from++;
	    case 6:
		*to++ = *from++;
	    case 5:
		*to++ = *from++;
	    case 4:
		*to++ = *from++;
	    case 3:
		*to++ = *from++;
	    case 2:
		*to++ = *from++;
	    case 1:
		*to++ = *from++;
	    } while (--n > 0);
	}
    }

    return count;
}

int zeds_device(char* from, char* to, int count)
{
	debug("start zeds_device from:%s to:%s count:%d", from, to, count); 
    {
	int n = (count + 7) / 8;
	debug("starts n: %d, count: %d, count%%8: %d",
	    n, count, count % 8);

	int r = count % 8;

	switch (count % 8) {
	case 0:
	again:
	    *to++ = *from++;

	case 7:
	    *to++ = *from++;
	case 6:
	    *to++ = *from++;
	case 5:
	    *to++ = *from++;
	case 4:
	    *to++ = *from++;
	case 3:
	    *to++ = *from++;
	case 2:
	    *to++ = *from++;
	case 1:
	    *to++ = *from++;
	    debug("last case: n=%d", n);
	    if (--n > 0) {
		debug("going again: n=%d", n);
		goto again;
	    }
	}
    }

    return count;
}

int is_valid_copy(char* data, int count, char expects)
{
    int i = 0;
    for (i = 0; i < count; i++) {
	if (data[i] != expects) {
	    log_err("[%d] %c != %c", i, data[i], expects);
	    return 0;
	}
    }

    return 1;
}

int main(int argc, char* argv[])
{
    const int size = 1005;
    char from[size] = { 'a' };
    char to[size] = { 'c' };
    int rc = 0;

    // setup the from to have some stuff
    memset(from, 'x', size);
    // set it to a failure mode
    memset(to, 'y', size);

    debug("array 'to' at 0 %c %d", to[0], to[0]);
    debug("array 'to' at 1 %c %d", to[1], to[1]);

    check(is_valid_copy(from, size, 'x'), "Not initialized from right.");
    check(is_valid_copy(to, size, 'y'), "Not initialized to right.");

    // use normal copy to
    rc = normal_copy(from, to, size);
    check(rc == size, "Normal copy failed: %d", rc);
    check(is_valid_copy(to, size, 'x'), "Normal copy failed.");

    // reset
    memset(to, 'y', size);

	clock_t start, end;
	double cpu_time_used;

    // duffs version
	start = clock();
	rc = duffs_device(from, to, size);
	check(rc == size, "Duff's device failed: %d", rc);
	check(is_valid_copy(to, size, 'x'), "Duff's device failed copy.");
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	debug("cpu_time_used:%f", cpu_time_used);
    // reset
    memset(to, 'y', size);

    // my version
	start = clock();
	rc = zeds_device(from, to, size);
	check(rc == size, "Zed's device failed: %d", rc);
	check(is_valid_copy(to, size, 'x'), "Zed's device failed copy.");
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	debug("cpu_time_used:%f", cpu_time_used);

	debug("finished");
    return 0;
error:
    return 1;
}
