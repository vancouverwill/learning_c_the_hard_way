#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "dbg.h"


/**
  * to run `./ex26 searchWord searchWord2`
  MVP
  
  * attempt with single file
  * Loop over hard coded list of log files and look for single word
  * load the list from ~/.logfind
  * allow 'and' functionality, easiest way is to first search for first word then on success check if file has same word
  * pick up whether flag '-o' is passed by command line as signifies or functionality
  * if or is switche ondo whole scan again for each word in list
  */

void die(const char *message)
{
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }
    exit(1);
}

int main(int argc, char *argv[])
{

	char* singleFileName = "/development//homestead/storage/logs/laravel-2015-03-22.log";
 	char* singleSearchWord = "php";
	printf("fileName:%s\n", singleFileName);

	for (int i = 0; i < argc; i++) {
		printf("%d:%s\n", i, argv[i]);
	}
    FILE* file = NULL;
    file = fopen(singleFileName, "r+");
	/*int rc = fread(conn->db, sizeof(struct Database), 1, file);*/
    if (file == NULL) die("Failed to load file.");
	char line [ 128 ]; /* or other suitable maximum line size */
	int lines = 0;
	while ( fgets ( line, sizeof line, file ) != NULL ) {
		lines++;
		printf("%s\n", line);
	}
	printf("total lines:%d\n", lines);
    fclose(file);
}
