#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "dbg.h"


//#define NDEBUG
char* RED="\033[0;31m";
char* NC="\033[0m";  // No Color
int maxLines = -1;
const int MAX_LINE_SIZE = 128;/* or other suitable maximum line size */
/**
  * to run `./ex26 searchWord searchWord2` 
IMPORTANT: special characters such as # need to put quotes around the string

  Requriments
  * [x] default search for lines which contain ALL search params, order irrelevant
  * [x] can do OR search when -o is passed as first arg
  * [] loads log files from `./.logfind`


  MVP Plan
  
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

/**
 * Remove trailing white space characters from string
 */
void trimTrailing(char * str)
{
    int index, i;

    /* Set default index */
    index = -1;

    /* Find last index of non-white space character */
    i = 0;
    while(str[i] != '\0')
    {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            index= i;
        }

        i++;
    }

    /* Mark next character to last non-white space character as NULL */
    str[index + 1] = '\0';
}

void search(char* singleFileName, int indexStartingSearchWord, int argc, char *argv[], int searchAll)
{
    FILE* file = NULL;
    file = fopen(singleFileName, "r+");
	trimTrailing(singleFileName);
	printf("open:%s!\n",singleFileName);
    if (file == NULL) die("Failed to load file.");
	char line [ MAX_LINE_SIZE ];
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

	char* logFileName = "./.logfind";
    FILE* logFile = NULL;
    logFile = fopen(logFileName, "r+");
    if (logFile == NULL) die("Failed to load log directory file.");
	char fileName [ MAX_LINE_SIZE ]; 
	while ( fgets ( fileName, sizeof fileName, logFile ) != NULL ) {
		printf("fileName:%s", fileName);
		search(fileName, indexStartingSearchWord, argc, argv, searchAll);
	}

	/*char* singleFileName = "/development//homestead/storage/logs/laravel-2015-03-22.log";*/

	for (int i = indexStartingSearchWord; i < argc; i++) {
		printf("%d:%s\n", i, argv[i]);
	}
	//search(singleFileName, indexStartingSearchWord, argc, argv, searchAll);
}
