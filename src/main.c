//
//  main.c
//  Sope
//
//  Created by Mateus Pedroza on 08/04/17.
//  Copyright © 2017 Mateus Pedroza. All rights reserved.
//
#include "sfind.h"

void parseArguments(char *argv[]);


void getCurrentPath(char path[]){
  char pathname[1024];

  if (getcwd(pathname, sizeof(pathname)) != NULL){
    strcpy(path, pathname);
  }else
  perror("getcwd() error");
}

/**
* Return home path
*/

void getHomePath(char pathname[]){
  struct passwd *info = getpwuid(getuid());

  strcpy(pathname, info->pw_dir);
}

int main(int argc, char *argv[]) {

  //  Check for invalid arguments
  if (argc >= 4 && argc < 6 && argv[1] != NULL && argv[2] != NULL && argv[3] != NULL && argv[4] != NULL) {
    parseArguments(argv);
  } else {
    printf("Usage: sfind [ '.', '/', '~' ] ['-name', '-type', '-perm'] [file] ['-print', '-delete', '-exec']\n");
    exit(1);
  }
}

void parseArguments(char *argv[]){
  char pathname[1024];
  //  arguments to parse
  char *searchDirectory = argv[1];
  char *searchParameter = argv[2];
  char *fileName = argv[3];
  char *command = argv[4];

  //  Directory '.','/','~'
  if (strcmp(searchDirectory, DIR_CURRENT) == 0){
    getCurrentPath(pathname);
  }
  else if (strcmp(searchDirectory, DIR_HOME) == 0){
    getHomePath(pathname);
  }
  else {
    strcpy(pathname, searchDirectory);
  }

  //  Search parameter '-name', '-type', '-perm'
  //  parameter name
  if (strcmp(searchParameter, PARAM_NAME) == 0){
    fileName = argv[3];
  }
  //  parameter type
  else if (strcmp(searchParameter, PARAM_TYPE) == 0){
    fileName = argv[3];
    //  file
    if (*fileName == 'f') {
      *fileName = DT_REG;
    }
    //  directory
    else if(*fileName == 'd'){
      *fileName = DT_DIR;
    }
    //  symbolic link
    else if (*fileName == 'l') {
      *fileName = DT_LNK;
    } else {
      printf("Invalid search type, possibles are: '%s' '%s' '%s'\n", "'f'- files", "'d' - directory", "'l' - symbolic link");
      exit(1);
    }
  }
  //  param perm
  else if (strcmp(searchParameter, PARAM_PERM) == 0){
    int i;
    //  check if argument is number
    if ((i = atoi(argv[3]))){
      fileName = argv[3];
    } else {
      printf("Invalid search permission, it should be a integer number\n");
      exit(1);
    }
  } else {
    printf("Invalid search parameter, possibles: '%s' '%s' '%s'\n",PARAM_NAME, PARAM_TYPE, PARAM_PERM);
    exit(1);
  }


  //  Command parameter '-print', '-delete', '-exec'
  if (strcmp(command, CMD_PRINT) == 0){

  }
  else if (strcmp(command, CMD_DELETE) == 0){

  }
  else if (strcmp(command, CMD_EXECUTE) == 0){} else {
    printf("Invalid command: possibles: '%s' '%s' '%s'\n",CMD_PRINT,CMD_DELETE, CMD_EXECUTE);
    exit(1);
  }

  //  start search
  printf("Sarch start at path: %s\n", pathname);
  sfind(fileName, searchDirectory, command, searchParameter);
}
