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

int handleFork(char pathname[], const char searchedText[], const char command[]){
  struct dirent *dirent;

  printf("--beginning of process: %d\n", getpid());

  //  Open directory
  DIR *directory = opendir(pathname);

  if (directory != NULL)
  {
    //printf("Directory opened\n");
  }
  else {
    perror("opendir() error");
    exit(1);
  }

  //  abrir pasta
  while ((dirent = readdir(directory))){
    printf("Ficheiro: %s\n", dirent->d_name);

    //  Check if dirent name is equal to file
    if (strcmp(dirent->d_name, searchedText) == 0) {
      handleFoundFile(*dirent, pathname, command);
      exit(0);
    }
    //  Check if dirent is a directory, and is diferent from "." and ".."
    else if (dirent->d_type == DT_DIR &&
      strcmp(dirent->d_name, "..") != 0 &&
      strcmp(dirent->d_name, ".") != 0){
        //  Found a directory, search in directory
        char newPath[1024];
        createSubpath(pathname, dirent, newPath);

        //  FORK: create two process
        handleFork(newPath, searchedText, command);
      }
    }

    printf("--end of process: %d\n", getpid());

    exit(0);
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

    //  FORK process
    pid_t pid = fork();

    if (pid < 0) {
      abort();
    } else if (pid == 0){
      // Child process
      printf("Child process: %d\n",getpid());
      //  Read directory file

      while ((dirent = readdir(directory))) {
        printf("File analized: %s\n", dirent->d_name);
        //  Check if dirent is a directory, and is diferent from "." and ".."
        //  If dirent name is equal searched text, print path
        if (strcmp(dirent->d_name, searchedText) == 0) {
          handleFoundFile(*dirent, pathname, command);
          exit(0);
        }
        else if (dirent->d_type == DT_DIR &&
          strcmp(dirent->d_name, "..") != 0 &&
          strcmp(dirent->d_name, ".") != 0){
            //  Found a directory, search in directory
            char newPath[1024];

            //  Create new path
            createSubpath(pathname, dirent, newPath);

            //  Search in new path recursively
            //sfind(searchedText, newPath, command);
          }
        }
      }
      else if (pid > 0){
        //  Parent process
        printf("Parent process: %d\n", getpid());

        int status;
        waitpid(pid, &status, 0);
      }

      printf("--end of the process: %d\n", getpid());

      closedir(directory);
      exit(0);
    }
