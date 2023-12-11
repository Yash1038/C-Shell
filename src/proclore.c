#include "../include/headers.h"

/*
proclore is used to obtain information regarding a process. If an argument is missing, print the information of your shell.

Information required to print :

pid
Process Status (R/R+/S/S+/Z)
Process group
Virtual Memory
Executable path of process

*/

// write a function proclore, which takes in the id, and prints out the above information. pid, process status, process group, virtual memory, executable path


// void proclore(pid_t id){

//     char path[1024];
//     sprintf(path, "/proc/%d/stat", id);

//     FILE *fp = fopen(path, "r");
//     if(fp == NULL){
//         perror("fopen");
//         return;
//     }

//     char *line = NULL;
//     size_t len = 0;
//     ssize_t read;

//     if((read = getline(&line, &len, fp)) != -1){
//         // printf("Retrieved line of length %zu:\n", read);
//         // printf("%s", line);

//         char *token = strtok(line, " ");
//         int i = 0;
//         while(token != NULL){
//             if(i == 0){
//                 printf("pid -- %s\n", token);
//             }else if(i == 2){
//                 printf("Process Status -- %s\n", token);
//             }else if(i == 3){
//                 printf("Memory -- %s\n", token);
//             }else if(i == 4){
//                 printf("Executable Path of process -- %s\n", token);
//             }

//             // also print the process group

//             token = strtok(NULL, " ");
//             i++;
//         }
//     }

//     fclose(fp);
//     if(line){
//         free(line);
//     }

// }

void proclore(pid_t pid) {
    printf("Process Information for PID %d:\n", pid);

    // Process Status
    char status;
    char status_path[256];
    snprintf(status_path, sizeof(status_path), "/proc/%d/stat", pid);
    FILE *status_file = fopen(status_path, "r");
    // if (status_file) {
    //     fscanf(status_file, "%*d %*s %c", &status);
    //     fclose(status_file);
    //     printf("Process Status: %c\n", status);
    // }

    if (status_file) {
        fscanf(status_file, "%*d %*s %c", &status);
        fclose(status_file);

        // Determine if the process is in the foreground
        if (tcgetpgrp(STDOUT_FILENO) == getpgid(pid)) {
            if (status == 'R' || status == 'S') {
                printf("Process Status: %c+\n", status);
            }
        }else{
            printf("Process Status: %c\n", status);
        }

    }

    // Process Group
    printf("Process Group: %d\n", getpgid(pid));

    // Virtual Memory
    struct sysinfo sys_info;
    if (sysinfo(&sys_info) == 0) {
        printf("Virtual Memory (Total): %ld KB\n", sys_info.totalram / 1024);
    }

    // Executable Path should be similar to that of how it is printed in the shell prompt

    char exe_path[256];
    snprintf(exe_path, sizeof(exe_path), "/proc/%d/exe", pid);
    char buffer[256];
    ssize_t len = readlink(exe_path, buffer, sizeof(buffer) - 1);
    if (len != -1) {
        buffer[len] = '\0';
        if(strncmp(buffer, homedir, strlen(homedir)) == 0){
            printf("Executable Path: ~%s\n", buffer + strlen(homedir));
        }else{
            printf("Executable Path: %s\n", buffer);
        }
        // printf("Executable Path: %s\n", buffer);
    }

    




    // char exe_path[256];
    // snprintf(exe_path, sizeof(exe_path), "/proc/%d/exe", pid);
    // char buffer[256];
    // ssize_t len = readlink(exe_path, buffer, sizeof(buffer) - 1);
    // if (len != -1) {
    //     buffer[len] = '\0';
    //     printf("Executable Path: %s\n", buffer);
    // }
}