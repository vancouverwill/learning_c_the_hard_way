#include <stdio.h>
#include <string.h>
#include "dbg.h"

int normal_copy(char *from, char *to, int count)
{
    int i = 0;

    for (i = 0; i < count; i++) {
        to[i] = from[i];
    }

    return i;
}

int duffs_device(char *from, char *to, int count)
{
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

int zeds_device(char *from, char *to, int count)
{
    {
        int n = (count + 7) / 8;
        debug("n starts: %d, count: %d, count%%8: %d", 
                n, count, count % 8);

        int r = count % 8;

        switch (count % 8) {
            case 0:
again:    *to++ = *from++;

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

int valid_copy(char *data, int count, char expects)
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

int main(int argc, char *argv[])
{
    const int size = 1005;
    char from[size] = { 'a' };
    char to[size] = { 'c' };
    int rc = 0;

    // setup the from to have some stuff
    memset(from, 'x', size);
    // set it to a failure mode
    memset(to, 'y', size);
	
	debug(
			"array to at 0 %c %d", to[0], to[0]);
		debug(	"array to at 0 %c %d", to[1], to[1
]);

    check(valid_copy(to, size, 'y'), "Not initialized right.");

    // use normal copy to 
    rc = normal_copy(from, to, size);
    check(rc == size, "Normal copy failed: %d", rc);
    check(valid_copy(to, size, 'x'), "Normal copy failed.");

    // reset
    memset(to, 'y', size);

    // duffs version
    rc = duffs_device(from, to, size);
    check(rc == size, "Duff's device failed: %d", rc);
    check(valid_copy(to, size, 'x'), "Duff's device failed copy.");

    // reset
    memset(to, 'y', size);

    // my version
    rc = zeds_device(from, to, size);
    check(rc == size, "Zed's device failed: %d", rc);
    check(valid_copy(to, size, 'x'), "Zed's device failed copy.");

    return 0;
error:
    return 1;
}
