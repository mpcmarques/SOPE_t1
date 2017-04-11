#ifndef S_FIND_H
#define  S_FIND_H

/*
* includes
*/
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "options.h"
#include <wait.h>


int sfind(const char searchedText[], const char pathname[], const char command[]);




#endif
