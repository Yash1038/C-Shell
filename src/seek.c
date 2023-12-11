#include "../include/headers.h"

/*
‘seek’ command looks for a file/directory in the specified target directory (or current if no directory is specified). It returns a list of relative paths (from target directory) of all matching files/directories
*/

// we have to search the entire file tree for it tho

// both files and directories are to be given


void seek(char *pwd, char *filename, char *orig_dir){
    // you have to search for <filename> in the entire file tree

    DIR *dir;
    struct dirent *dp;

    dir = opendir(pwd);

    if(dir == NULL){
        perror("opendir");
        return;
    }

    // output both files and directories in entirety of subtree

    while((dp = readdir(dir)) != NULL){

        char temp_file[255];
        strcpy(temp_file, dp->d_name);
        if(compare_f_w_s(temp_file, filename) == 0){
            char temp_address[255];
            // temp[0] = '\0';
            // strcpy(temp_address, ".");
            strcpy(temp_address, pwd);
            strcat(temp_address, "/");
            strcat(temp_address, dp->d_name);

            char rela_path[255];
            rela_path[0] = '\0';
            strcat(rela_path, ".");
            // rela_path = rel_path(temp_address, orig_dir);
            strcat(rela_path, rel_path(temp_address, orig_dir));
            printf("%s\n", rela_path);
            
        }

        
        if(dp->d_name[0] != '.'){

            struct stat fileStat;
            if(stat(dp->d_name, &fileStat) < 0){
                // perror("stat");
                return;
            }

            

            if(S_ISDIR(fileStat.st_mode)){
                // this is a directory
                // printf(BOLD BLUE "%s  " RESET, dp->d_name);
                char pwd_temp[255];
                getcwd(pwd_temp, 255);
                chdir(dp->d_name);
                char pwd_target[255];
                getcwd(pwd_target, 255);
                seek(pwd_target, filename, orig_dir);
                chdir(pwd_temp);
            }
        }
    }

    return;
}


void seek_d(char *pwd, char *filename, char *orig_dir){

    DIR *dir;
    struct dirent *dp;

    dir = opendir(pwd);

    if(dir == NULL){
        perror("opendir");
        return;
    }

    while((dp = readdir(dir)) != NULL){

        
        if(dp->d_name[0] != '.'){

            struct stat fileStat;
            if(stat(dp->d_name, &fileStat) < 0){
                // perror("stat");
                return;
            }

            

            if(S_ISDIR(fileStat.st_mode)){
                // this is a directory
                // printf(BOLD BLUE "%s  " RESET, dp->d_name);
                char pwd_temp[255];
                getcwd(pwd_temp, 255);
                chdir(dp->d_name);
                char pwd_target[255];
                getcwd(pwd_target, 255);
                seek_d(pwd_target, filename, orig_dir);
                chdir(pwd_temp);

                char temp_file[255];
                strcpy(temp_file, dp->d_name);
                if(compare_f_w_s(temp_file, filename) == 0){
                    char temp_address[255];
                    // temp[0] = '\0';
                    // strcpy(temp_address, ".");
                    strcpy(temp_address, pwd);
                    strcat(temp_address, "/");
                    strcat(temp_address, dp->d_name);

                    char rela_path[255];
                    rela_path[0] = '\0';
                    strcat(rela_path, ".");
                    // rela_path = rel_path(temp_address, orig_dir);
                    strcat(rela_path, rel_path(temp_address, orig_dir));
                    printf("%s\n", rela_path);
                    
                }
            }
        }
    }
}

void seek_f(char *pwd, char *filename, char *orig_dir){
    // this will output only files

    DIR *dir;
    struct dirent *dp;

    dir = opendir(pwd);

    if(dir == NULL){
        perror("opendir");
        return;
    }

    while((dp = readdir(dir)) != NULL){

        
        if(dp->d_name[0] != '.'){

            struct stat fileStat;
            if(stat(dp->d_name, &fileStat) < 0){
                // perror("stat");
                return;
            }

            

            if(S_ISDIR(fileStat.st_mode)){
                // this is a directory
                // printf(BOLD BLUE "%s  " RESET, dp->d_name);
                char pwd_temp[255];
                getcwd(pwd_temp, 255);
                chdir(dp->d_name);
                char pwd_target[255];
                getcwd(pwd_target, 255);
                seek_f(pwd_target, filename, orig_dir);
                chdir(pwd_temp);
            }
            else{
                // this is a file
                char temp_file[255];
                strcpy(temp_file, dp->d_name);
                if(compare_f_w_s(temp_file, filename) == 0){
                    char temp_address[255];
                    // temp[0] = '\0';
                    // strcpy(temp_address, ".");
                    strcpy(temp_address, pwd);
                    strcat(temp_address, "/");
                    strcat(temp_address, dp->d_name);

                    char rela_path[255];
                    rela_path[0] = '\0';
                    strcat(rela_path, ".");
                    // rela_path = rel_path(temp_address, orig_dir);
                    strcat(rela_path, rel_path(temp_address, orig_dir));
                    printf("%s\n", rela_path);
                    
                }
            }
        }
    }
}


void seek_ef(char *pwd, char *filename, char *orig_dir, char *seek_temp_path){
    // this will output only files

    DIR *dir;
    struct dirent *dp;

    dir = opendir(pwd);

    // do malloc for rela path

    char *rela_path = (char *)malloc(255 * sizeof(char));
    rela_path[0] = '\0';

    if(dir == NULL){
        perror("opendir");
        return;
    }

    while((dp = readdir(dir)) != NULL){

        
        if(dp->d_name[0] != '.'){

            struct stat fileStat;
            if(stat(dp->d_name, &fileStat) < 0){
                // perror("stat");
                return;
            }

            

            if(S_ISDIR(fileStat.st_mode)){
                // this is a directory
                // printf(BOLD BLUE "%s  " RESET, dp->d_name);
                char pwd_temp[255];
                getcwd(pwd_temp, 255);
                chdir(dp->d_name);
                char pwd_target[255];
                getcwd(pwd_target, 255);
                seek_ef(pwd_target, filename, orig_dir, seek_temp_path);
                chdir(pwd_temp);
            }
            else{
                // this is a file
                char temp_file[255];
                strcpy(temp_file, dp->d_name);
                if(compare_f_w_s(temp_file, filename) == 0){
                    char temp_address[255];
                    // temp[0] = '\0';
                    // strcpy(temp_address, ".");
                    strcpy(temp_address, pwd);
                    strcat(temp_address, "/");
                    strcat(temp_address, dp->d_name);

                    // char rela_path[255];
                    // rela_path[0] = '\0';
                    strcat(rela_path, ".");
                    // rela_path = rel_path(temp_address, orig_dir);
                    strcat(rela_path, rel_path(temp_address, orig_dir));
                    seek_count++;
                    //printf("%s\n", rela_path);
                    strcpy(seek_temp_path, rela_path);
                    
                }
            }
        }
    }

}

void seek_ed(char *pwd, char *filename, char *orig_dir, char *seek_temp_path){
    // this is similar to seek_ef but it will output only directories

    DIR *dir;
    struct dirent *dp;

    dir = opendir(pwd);

    // do malloc for rela path

    char *rela_path = (char *)malloc(255 * sizeof(char));
    rela_path[0] = '\0';

    if(dir == NULL){
        perror("opendir");
        return;
    }

    while((dp = readdir(dir)) != NULL){

        
        if(dp->d_name[0] != '.'){

            struct stat fileStat;
            if(stat(dp->d_name, &fileStat) < 0){
                // perror("stat");
                return;
            }

            

            if(S_ISDIR(fileStat.st_mode)){
                // this is a directory
                // printf(BOLD BLUE "%s  " RESET, dp->d_name);
                char temp_file[255];
                strcpy(temp_file, dp->d_name);
                if(compare_f_w_s(temp_file, filename) == 0){
                    char temp_address[255];
                    // temp[0] = '\0';
                    // strcpy(temp_address, ".");
                    strcpy(temp_address, pwd);
                    strcat(temp_address, "/");
                    strcat(temp_address, dp->d_name);

                    // char rela_path[255];
                    // rela_path[0] = '\0';
                    strcat(rela_path, ".");
                    // rela_path = rel_path(temp_address, orig_dir);
                    strcat(rela_path, rel_path(temp_address, orig_dir));
                    seek_count++;
                    //printf("%s\n", rela_path);
                    strcpy(seek_temp_path, rela_path);
                    
                }
                char pwd_temp[255];
                getcwd(pwd_temp, 255);
                chdir(dp->d_name);
                char pwd_target[255];
                getcwd(pwd_target, 255);
                seek_ed(pwd_target, filename, orig_dir, seek_temp_path);
                chdir(pwd_temp);
            }
        }
    }
}

