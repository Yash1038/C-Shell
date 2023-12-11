#include "../include/headers.h"
// /*

// This specification requires you to print a list of all the processes currently running that were spawned by your shell in lexicographic order. This list should contain the following information about all processes :

// Command Name
// pid
// state : running or stopped

// */

void activities(){

    struct dirent *de;  // Pointer for directory entry
    DIR *dr = opendir("/proc");
    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory" );
        return;
    }

    printf("PID\t\t\tName\t\t\tStatus\n");

    // First print the shell process
    
    printf("%d\t\t\t%s\t\t\t%s\n", getpid(), "yash", "running");

    while((de = readdir(dr)) != NULL){
        if(isdigit(de->d_name[0])){
            // printf("%s\n", de->d_name);
            int pid = atoi(de->d_name);
            char path[100];
            strcpy(path, "/proc/");
            strcat(path, de->d_name);
            strcat(path, "/stat");
            // printf("%s\n", path);

            FILE *fp = fopen(path, "r");
            if(fp == NULL){
                printf("Error opening file\n");
                return;
            }

            char *line = NULL;
            size_t len = 0;
            ssize_t read;

            if((read = getline(&line, &len, fp)) != -1){
                // printf("%s\n", line);
                char *token = strtok(line, " ");
                int i = 0;
                char *tokens[100];
                while(token != NULL){
                    tokens[i] = token;
                    token = strtok(NULL, " ");
                    i++;
                }

                // printf("%s\n", tokens[2]);
                // printf("%s\n", tokens[3]);

                // get status of the process given a pid and then print it

                // if it is running, then print running, else stopped

                if(atoi(tokens[3]) == getpid()){


                    if(strcmp(tokens[2], "R") == 0 || strcmp(tokens[2], "S") == 0){
                        printf("%d\t\t\t%s\t\t\t%s\n", pid, tokens[1], "running");
                    }
                    else if(tokens[2][0] == 'T'){
                        printf("%d\t\t\t%s\t\t\t%s\n", pid, tokens[1], "stopped");
                    }
                }
            }
        }
    }
}

