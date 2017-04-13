#ifndef S_FIND_H
#define  S_FIND_H

/*
* includes
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <pwd.h>
#include <sys/stat.h>
#include "str.h"
#include <sys/types.h>
#include <dirent.h>
#include "options.h"
#include <wait.h>
#include <signal.h>


int sfind(const char *searchedText, const char pathname[], const char command[], const char searchParameter[], const char execute[]);




#endif
