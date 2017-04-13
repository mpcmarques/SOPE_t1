//
//  main.c
//  Sope
//
//  Created by Mateus Pedroza on 08/04/17.
//  Copyright © 2017 Mateus Pedroza. All rights reserved.
//
#include "sfind.h"

void parseArguments(int argc, char *argv[]);


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

static void sig_usr(int signo){

  //  Check if received signal is SIGINT
 if (signo == SIGINT){

   char opt;
   // Ask user to terminate program
  printf("Are you sure you want to terminate (Y/N)?\n");
  scanf("%c", &opt);

  if (opt == 'Y') {
    exit(0);
  }
  else if (opt == 'N') {
    printf("Resuming program...\n");
    sleep(1);
  } else {
    printf("Input is not valid, resuming program in 2 seconds...\n");
    sleep(2);
  }
  }
 return;
}

int main(int argc, char *argv[]) {
  struct sigaction action;
  //  setup signal action
  action.sa_handler = sig_usr;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;
  sigaction(SIGINT, &action, NULL);

  //  Check for invalid arguments
  if (argc >= 4 && argv[1] != NULL && argv[2] != NULL && argv[3] != NULL && argv[4] != NULL) {
    parseArguments(argc, argv);
  } else {
    printf("Usage: sfind [ '.', '/', '~' ] ['-name', '-type', '-perm'] [file] ['-print', '-delete', '-exec']\n");
    exit(1);
  }
}

void parseArguments(int argc, char *argv[]){
  char pathname[1024];
  //  arguments to parse
  char *searchDirectory = argv[1];
  char *searchParameter = argv[2];
  char *fileName = argv[3];
  char *command = argv[4];
  char *execute;

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
  else if (strcmp(command, CMD_EXECUTE) == 0){
    int i = 5;
    char newCommand[1024] = "";
    execute = argv[5];
    int isCommandValid = 0;

    while (i < argc){
      strcat(newCommand, argv[i]);
      strcat(newCommand, " ");
      //  command need to finish with ;
      if (strcmp(argv[i], ";") == 0){
        isCommandValid = 1;
      }
      i++;
    }

    //  execute = newCommand
    strcpy(execute, newCommand);

    if((execute == NULL) || !isCommandValid) {
      printf("Function is empty, usage is: -exec command \\;\n");
      exit(1);
    }
  } else {
    printf("Invalid command: possibles: '%s' '%s' '%s command \\;\n",CMD_PRINT,CMD_DELETE, CMD_EXECUTE);
    exit(1);
  }

  //  start search  
  sfind(fileName, pathname, command, searchParameter, execute);
}
