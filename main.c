//
//  main.c
//  Sope
//
//  Created by Mateus Pedroza on 08/04/17.
//  Copyright © 2017 Mateus Pedroza. All rights reserved.
//

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>

/** 
 Gets default path
 @param path  Empty char vector that will be filled with path;
 */
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
void handleFoundFile(struct dirent dirent, char path[], const char command[]){
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

int sfind(const char searchedText[], char pathname[], const char command[]){
    struct dirent *dirent = NULL;
    
    //  Open directory
    DIR *directory = opendir(pathname);
    
    if (directory != NULL)
    { // printf("Directory opened\n");
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




int main(int argc, const char * argv[]) {
    // insert code here...
    
    char pathname[1024];
    const char *searchType = argv[1];
    const char *searchParameter = argv[2];
    const char *fileName = argv[3];
    const char *command = argv[4];
    
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
    printf("%s\n", pathname);
    sfind(fileName, pathname, command);
    
    return 0;
}
