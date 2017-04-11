#include "sfind.h"


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

  exit(0);
}

void createSubpath(const char *originalPath, struct dirent *directory, char *finalPath){
  char newPath[1024];
  //  Create new path
  strcpy(newPath, originalPath);
  strcat(newPath, "/");
  strcat(newPath, directory->d_name);
  //  Modify final path
  strcpy(finalPath, newPath);
}

void handleFork(const char searchedText[],const char pathname[], const char command[]){
  //  FORK process
  pid_t pid = fork();

  if (pid < 0 ) {
    perror("error forking");
    abort();

  } else if (pid > 0) {
    /* parent */
    int status;
    waitpid(pid, &status, 0);
  } else  if (pid == 0){
    /* child*/
    sfind(searchedText, pathname, command);
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


    //  If dirent name is equal searched text, print path
    if (strcmp(dirent->d_name, searchedText) == 0) {
      handleFoundFile(*dirent, pathname, command);
    }
    //  Check if dirent is a directory, and is diferent from "." and ".."
    else if (dirent->d_type == DT_DIR &&
      strcmp(dirent->d_name, "..") != 0 &&
      strcmp(dirent->d_name, ".") != 0){
        //  Found a directory, search in directory
        char newPath[1024];

        //  Create new path
        strcpy(newPath, pathname);
        strcat(newPath, "/");
        strcat(newPath, dirent->d_name);

        //  Search in new path recursively
        handleFork(searchedText, newPath, command);
      }
    }


    closedir(directory);
    exit(0);
  }
