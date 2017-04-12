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

void handleFork(const unsigned char *searchedText,const char pathname[], const char command[], const char searchParameter[]){
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
    sfind(searchedText, pathname, command, searchParameter);
  }
}

void fileLogic(const unsigned char *searchedText, const char pathname[], const char command[], const char searchParameter[], struct dirent *dirent, struct stat statsbuf){
  //  If dirent name is equal searched name text, handle it.
  if (strcmp(PARAM_NAME, searchParameter)== 0 && strcmp(dirent->d_name, (char*)searchedText) == 0) {
    handleFoundFile(*dirent, pathname, command);
  }
  //  If dirent type is equal file searched type
  else if (strcmp(PARAM_TYPE, searchParameter) == 0 && dirent->d_type == *searchedText) {
    handleFoundFile(*dirent, pathname, command);
  }
  //  If dirent perm is equal file searched perm
  else if (strcmp(PARAM_PERM, searchParameter) == 0 ){
    /* code */
    //  fstt

    printf("%o %lo\n", (statsbuf.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO)), strtoul((char*)searchedText, (char**)&searchedText, 8));
  }
  //  Check if dirent is a directory, and is diferent from "." and ".."
  else if (S_ISDIR(statsbuf.st_mode) && (!S_ISLNK(statsbuf.st_mode)) && strcmp(dirent->d_name, "..") != 0 && strcmp(dirent->d_name, ".") != 0){
    //  Found a directory, search in directory
    //  create file path
    char filePath[1024];
    createSubpath(pathname, dirent, filePath);

    handleFork(searchedText, filePath, command, searchParameter);
  }
}

int sfind(const unsigned char *searchedText, const char pathname[], const char command[], const char searchParameter[]){
  struct dirent *dirent = NULL;
  struct stat statbuf;
  DIR *directory;

  //  Open directory
  if((directory = opendir(pathname)) == NULL){
    perror("opendir() error");
    exit(1);
  }

  //  change directory to actual path
  chdir(pathname);

  //  Read directory file
  while ((dirent = readdir(directory)) != NULL) {
  //  printf("Analyzing: %s/%s\n", pathname, dirent->d_name);

    //  Read file status
    if (lstat(dirent->d_name, &statbuf) == -1) {
      //  File couldn't be read
      perror("stat() error");
    } else {
      //  File could be read
      fileLogic(searchedText, pathname, command, searchParameter, dirent, statbuf);
    }
  }

  closedir(directory);
  exit(0);
}
