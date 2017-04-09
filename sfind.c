#include "sfind.h"



void getDefaultPath(char path[]){
  char pathname[1024];

  if (getcwd(pathname, sizeof(pathname)) != NULL){
    strcpy(path, pathname);
  }else
  perror("getcwd() error");
}

/**
*  Founded file action handler
*/
void handleFoundFile(struct dirent dirent, const char path[], const char command[]){
  char newPath[1024];

  //  Create new path
  strcpy(newPath, path);
  strcat(newPath, "/");
  strcat(newPath, dirent.d_name);

  if (strcmp(command, "-print") == 0){
    printf("%s\n", newPath);
  }
  else if (strcmp(command, "-delete") == 0){
    remove(newPath);
  }
}

int sfind(const char searchedText[], const char pathname[], const char command[]){
  struct dirent *dirent = NULL;

  //  Open directory
  DIR *directory = opendir(pathname);

  if (directory != NULL)
  {
    //printf("Directory opened\n");
  }
  else
  perror("opendir() error");

  //  Read directory file

  while ((dirent = readdir(directory))) {

    //  Check if dirent is a directory, and is diferent from "." and ".."
    if (dirent->d_type == DT_DIR &&
      strcmp(dirent->d_name, "..") != 0 &&
      strcmp(dirent->d_name, ".") != 0){
        //  Found a directory, search in directory
        char newPath[1024];

        //  Create new path
        strcpy(newPath, pathname);
        strcat(newPath, "/");
        strcat(newPath, dirent->d_name);

        //  Search in new path recursively
        sfind(searchedText, newPath, command);

      }

      //  If dirent name is equal searched text, print path
      if (strcmp(dirent->d_name, searchedText) == 0) {
        handleFoundFile(*dirent, pathname, command);
      }
    }


    closedir(directory);
    return 1;
  }

  /**
  * Return home path
  */

  void getHomePath(char pathname[]){
    struct passwd *info = getpwuid(getuid());

    strcpy(pathname, info->pw_dir);
  }

  void startSearch(const char *searchType, const char *searchParameter, const char*fileName, const char* command){
    char pathname[1024];

    // searchtypes possibles : . ~ /
    // .
    if (strcmp(searchType, ".") == 0 ){
      getDefaultPath(pathname);
    }
    else if(strcmp(searchType, "~") == 0){
      getHomePath(pathname);
    }

    //  searchparameters possibles : -name -type -perm

    //  commands possible: -delete -read
    printf("Sarch start at path: %s\n", pathname);
    sfind(fileName, pathname, command);
  }
