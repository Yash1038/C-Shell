#include "../include/headers.h"

// #define PATH_MAX 255

void peek(char *pwd){
    DIR *dir;
    struct dirent *dp;

    // printf("%s", pwd);

    dir = opendir(pwd);

    if(dir == NULL){
        perror("opendir");
        return;
    }

    while((dp = readdir(dir)) != NULL){
        if(dp->d_name[0] != '.'){
            struct stat fileStat;
            if(stat(dp->d_name, &fileStat) < 0){
                perror("stat");
                return;
            }

            if(S_ISDIR(fileStat.st_mode)){
                // this is a directory
                printf(BOLD BLUE "%s  " RESET, dp->d_name);
            }else if(fileStat.st_mode & S_IXUSR){
                // this is an executable
                printf(BOLD GREEN "%s  " RESET, dp->d_name);
            }else{
                // this is a normal file
                printf("%s  ", dp->d_name);
            }
        }
    }
    printf("\n");

}


void peek_a(char *pwd){

    DIR *dir;
    struct dirent *dp;

    dir = opendir(pwd);

    if(dir == NULL){
        perror("opendir");
        return;
    }

    while((dp = readdir(dir)) != NULL){
        struct stat fileStat;
        if(stat(dp->d_name, &fileStat) < 0){
            perror("stat");
            return;
        }

        if(S_ISDIR(fileStat.st_mode)){
            // this is a directory
            printf(BOLD BLUE "%s  " RESET, dp->d_name);
        }else if(fileStat.st_mode & S_IXUSR){
            // this is an executable
            printf(BOLD GREEN "%s  " RESET, dp->d_name);
        }else{
            // this is a normal file
            printf("%s  ", dp->d_name);
        }
    }

    printf("\n");
}


void peek_l(char *pwd){

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
                perror("stat");
                return;
            }

            if(S_ISDIR(fileStat.st_mode)){
                // this is a directory
                printf("d");
            }else if(fileStat.st_mode & S_IXUSR){
                // this is an executable
                printf("x");
            }else{
                // this is a normal file
                printf("-");
            }

            if(fileStat.st_mode & S_IRUSR){
                printf("r");
            }else{
                printf("-");
            }

            if(fileStat.st_mode & S_IWUSR){
                printf("w");
            }else{
                printf("-");
            }

            if(fileStat.st_mode & S_IXUSR){
                printf("x");
            }else{
                printf("-");
            }

            if(fileStat.st_mode & S_IRGRP){
                printf("r");
            }else{
                printf("-");
            }

            if(fileStat.st_mode & S_IWGRP){
                printf("w");
            }else{
                printf("-");
            }

            if(fileStat.st_mode & S_IXGRP){
                printf("x");
            }else{
                printf("-");
            }

            if(fileStat.st_mode & S_IROTH){
                printf("r");
            }else{
                printf("-");
            }

            if(fileStat.st_mode & S_IWOTH){
                printf("w");
            }else{
                printf("-");
            }

            if(fileStat.st_mode & S_IXOTH){
                printf("x");
            }else{
                printf("-");
            }

            printf(" %ld ", fileStat.st_nlink);

            struct passwd *pw = getpwuid(fileStat.st_uid);
            if(pw != NULL){
                printf("%s ", pw->pw_name);
            }else{
                printf("%d ", fileStat.st_uid);
            }

            // group name

            struct group *gr = getgrgid(fileStat.st_gid);
            if(gr != NULL){
                printf("%s ", gr->gr_name);
            }else{
                printf("%d ", fileStat.st_gid);
            }

            // size of the file
            printf("%ld ", fileStat.st_size);

            // last modified time
            char *time = ctime(&fileStat.st_mtime);
            time[strlen(time) - 1] = '\0';
            printf("%s ", time);

            //name of the file based on type
            if(S_ISDIR(fileStat.st_mode)){
                // this is a directory
                printf(BOLD BLUE "%s " RESET, dp->d_name);
            }else if(fileStat.st_mode & S_IXUSR){
                // this is an executable
                printf(BOLD GREEN "%s " RESET, dp->d_name);
            }else{
                // this is a normal file
                printf("%s ", dp->d_name);
            }

            printf("\n");

        }
    }
}

void peek_al(char *pwd){

    DIR *dir;
    struct dirent *dp;

    dir = opendir(pwd);

    if(dir == NULL){
        perror("opendir");
        return;
    }

    while((dp = readdir(dir)) != NULL){
        struct stat fileStat;
        if(stat(dp->d_name, &fileStat) < 0){
            perror("stat");
            return;
        }

        if(S_ISDIR(fileStat.st_mode)){
            // this is a directory
            printf("d");
        }else if(fileStat.st_mode & S_IXUSR){
            // this is an executable
            printf("x");
        }else{
            // this is a normal file
            printf("-");
        }

        if(fileStat.st_mode & S_IRUSR){
            printf("r");
        }else{
            printf("-");
        }

        if(fileStat.st_mode & S_IWUSR){
            printf("w");
        }else{
            printf("-");
        }

        if(fileStat.st_mode & S_IXUSR){
            printf("x");
        }else{
            printf("-");
        }

        if(fileStat.st_mode & S_IRGRP){
            printf("r");
        }else{
            printf("-");
        }

        if(fileStat.st_mode & S_IWGRP){
            printf("w");
        }else{
            printf("-");
        }

        if(fileStat.st_mode & S_IXGRP){
            printf("x");
        }else{
            printf("-");
        }

        if(fileStat.st_mode & S_IROTH){
            printf("r");
        }else{
            printf("-");
        }

        if(fileStat.st_mode & S_IWOTH){
            printf("w");
        }else{
            printf("-");
        }

        if(fileStat.st_mode & S_IXOTH){
            printf("x");
        }else{
            printf("-");
        }

        printf(" %ld ", fileStat.st_nlink);

        // owner name
        struct passwd *pw = getpwuid(fileStat.st_uid);
        if(pw != NULL){
            printf("%s ", pw->pw_name);
        }else{
            printf("%d ", fileStat.st_uid);
        }

        // group name
        struct group *gr = getgrgid(fileStat.st_gid);
        if(gr != NULL){
            printf("%s ", gr->gr_name);
        }else{
            printf("%d ", fileStat.st_gid);
        }

        // size of the file
        printf("%ld ", fileStat.st_size);

        // last modified time
        char *time = ctime(&fileStat.st_mtime);
        time[strlen(time) - 1] = '\0';
        printf("%s ", time);

        //name of the file based on type
        if(S_ISDIR(fileStat.st_mode)){
            // this is a directory
            printf(BOLD BLUE "%s " RESET, dp->d_name);
        }else if(fileStat.st_mode & S_IXUSR){
            // this is an executable
            printf(BOLD GREEN "%s " RESET, dp->d_name);
        }else{
            // this is a normal file
            printf("%s ", dp->d_name);
        }
        printf("\n");
    }
}