#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "dbg.h"


//#define NDEBUG
char* RED="\033[0;31m";
char* NC="\033[0m";  // No Color
int maxLines = -1;
/**
  * to run `./ex26 searchWord searchWord2` 
IMPORTANT: special characters such as # need to put quotes around the string

  Requriments
  * [x] default search for lines which contain ALL search params, order irrelevant
  * [x] can do OR search when -o is passed as first arg
  * [] loads log files from `./.logfind`


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

char* get_colored_search_word(char* needle)
{
	char* singleSearchWordWithWarning;
	asprintf(&singleSearchWordWithWarning, "%s%s%s", RED, needle, NC);
	return singleSearchWordWithWarning;
}	

int main(int argc, char *argv[])
{
	int indexStartingSearchWord = 1;
	int searchAll = 1;
	debug("main begin:%s", argv[1]);

	if (strncmp(argv[1],"-o", 2) == 0) {
		debug("setting up OR");
		searchAll = 0;
		printf("search OR\n");
		indexStartingSearchWord = 2;
	} else {
		debug("setting up ALL");
		printf("search ALL\n");
	} 
	debug("have set search type");

	char* singleFileName = "/development//homestead/storage/logs/laravel-2015-03-22.log";

	for (int i = indexStartingSearchWord; i < argc; i++) {
		printf("%d:%s\n", i, argv[i]);
	}
    FILE* file = NULL;
    file = fopen(singleFileName, "r+");
    if (file == NULL) die("Failed to load file.");
	char line [ 128 ]; /* or other suitable maximum line size */
	int lines = 0;
	int matches = 0;
	int matches_per_line = 0;
	while ( fgets ( line, sizeof line, file ) != NULL ) {
		lines++;
		#ifdef NDEBUG
			printf("%s\n", line);
		#endif
		char * pch;
		char * needle;
		for (int i = indexStartingSearchWord; i < argc; i++) {
			needle = argv[i];
			pch = strstr(line, needle);
			if (pch) {
				matches_per_line++;
				strncpy(pch, get_colored_search_word(needle), strlen(get_colored_search_word(needle))); 
			}
		}
		if (searchAll == 0 && matches_per_line > 0) {
				matches++;
				printf("%s\n", line);	
		} else if (matches_per_line >= argc - indexStartingSearchWord) {
				matches++;
				printf("%s\n", line);	
		}

		if (maxLines != -1 && lines > maxLines) {
			break;
		}
		matches_per_line = 0;		
	}
	printf("total lines:%s%d%s\n", RED, lines, NC);
	printf("total matches:%d\n", matches);
    fclose(file);
}
