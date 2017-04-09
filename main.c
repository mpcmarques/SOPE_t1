//
//  main.c
//  Sope
//
//  Created by Mateus Pedroza on 08/04/17.
//  Copyright © 2017 Mateus Pedroza. All rights reserved.
//


#include "options.h"
#include "sfind.h"

void parseArguments(char *argv[]);

  int main(int argc, char *argv[]) {

    //  Check for invalid arguments
    if (argc < 4) {
      printf("Usage:\n sfind [ '.', '/', '~' ] ['-name', '-type', '-perm'] [file] ['-print', '-delete', '-exec']\n");
      exit(1);
    } else {
      parseArguments(argv);
    }
  }


  void parseArguments(char *argv[]){
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

        }
        else if (strcmp(searchDirectory, DIR_HOME) == 0){

        }
        else if (strcmp(searchDirectory, DIR_ROOT) == 0){

        }

        //  Search parameter '-name', '-type', '-perm'
        if ((searchParameter = argv[2]) == NULL) {
          /* code */
        }
        else if (strcmp(searchParameter, PARAM_NAME) == 0){

        }
        else if (strcmp(searchParameter, PARAM_TYPE) == 0){

        }
        else if (strcmp(searchParameter, PARAM_PERM) == 0){

        }

        //  Command parameter '-print', '-delete', '-exec'
        if ((command = argv[4]) == NULL) {
          /* code */
        }
        else if (strcmp(command, CMD_PRINT) == 0){

        }
        else if (strcmp(command, CMD_DELETE) == 0){

        }
        else if (strcmp(command, CMD_EXECUTE) == 0){}
  }
