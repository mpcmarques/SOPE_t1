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
  if (argc >= 4 && argc < 6) {
    parseArguments(argv);
  } else {
    printf("Usage:\n sfind [ '.', '/', '~' ] ['-name', '-type', '-perm'] [file] ['-print', '-delete', '-exec']\n");
    exit(1);
  }
}

void parseArguments(char *argv[]){
  char pathname[1024];
  //  arguments to parse
  char *searchDirectory;
  char *searchParameter;
  char *fileName;
  char *command;

  //  Directory '.','/','~'
  if ((searchDirectory = argv[1]) == NULL) {
    /* code */
  }
  else if (strcmp(searchDirectory, DIR_CURRENT) == 0){
    getCurrentPath(pathname);
  }
  else if (strcmp(searchDirectory, DIR_HOME) == 0){
    getHomePath(pathname);
  }
  else {
    strcpy(pathname, searchDirectory);
  }

  //  Search parameter '-name', '-type', '-perm'
  if ((searchParameter = argv[2]) == NULL) {
    /* code */
  }
  else if (strcmp(searchParameter, PARAM_NAME) == 0){
      if((fileName = argv[3]) != NULL){}
  }
  else if (strcmp(searchParameter, PARAM_TYPE) == 0){

  }
  else if (strcmp(searchParameter, PARAM_PERM) == 0){

  } else {
    printf("Invalid search parameter, possibles: '%s' '%s' '%s'\n",PARAM_NAME, PARAM_TYPE, PARAM_PERM);
  }


  //  Command parameter '-print', '-delete', '-exec'
  if ((command = argv[4]) == NULL) {
    /* code */
  }
  else if (strcmp(command, CMD_PRINT) == 0){

  }
  else if (strcmp(command, CMD_DELETE) == 0){

  }
  else if (strcmp(command, CMD_EXECUTE) == 0){} else {
    printf("Invalid command: possibles: '%s' '%s' '%s'\n",CMD_PRINT,CMD_DELETE, CMD_EXECUTE);
  }


  //  start search
  printf("Sarch start at path: %s\n", pathname);
  sfind(fileName, pathname, command);
}
