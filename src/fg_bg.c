#include "../include/headers.h"

#define MAX_BACKGROUND 100

struct BackgroundProcess{
    __pid_t pid;
    char *command;
};

struct BackgroundProcess bg_processes[MAX_BACKGROUND];
// int num_bg_proc = 0;

int compare(const void *a, const void *b){
    struct BackgroundProcess *bg1 = (struct BackgroundProcess *)a;
    struct BackgroundProcess *bg2 = (struct BackgroundProcess *)b;

    return bg1->pid - bg2->pid;
}

// void activities(){
//     // perform a qsort on the bg_processes array based on id numbers
//     // then print the array, the command name and the status as running or stopped

//     qsort(bg_processes, num_bg_proc, sizeof(struct BackgroundProcess), compare);

//     printf("PID\t\t\tName\t\t\tStatus\n");
//     printf("%d\t\t\t%s\t\t\t%s\n", getpid(), "yash", "running");

//     for(int i=0; i < num_bg_proc; i++){
        
//         int status;
//         pid_t result = waitpid(bg_processes[i].pid, &status, WNOHANG);

//         if(result == 0){
//             printf("%d\t\t\t%s\t\t\t%s\n", bg_processes[i].pid, bg_processes[i].command, "running");
//         }else if(result > 0){
//             if(WIFSIGNALED(status)){
//                 printf("%d\t\t\t%s\t\t\t%s\n", bg_processes[i].pid, bg_processes[i].command, "stopped");
//             }
//         }
//     }

// }

void check_bg_process(){

    //printf("Checking the background processes\n %d", num_bg_proc);
    for(int i=0; i< num_bg_proc;i++){
        // printf("pid %d\n", bg_processes[i].pid);
        int status;
        pid_t result = waitpid(bg_processes[i].pid, &status, WNOHANG);
        // printf("result %d\n", result);
        if(result > 0){
            // printf("Background process %s with pid %d exited with status %d\n", bg_processes[i].command, bg_processes[i].pid, status);

            if(WIFEXITED(status)){
                printf("%s exited normally (%d)\n", bg_processes[i].command, bg_processes[i].pid);
            }else if(WIFSIGNALED(status)){
                printf("%s exited abnormally (%d)\n", bg_processes[i].command, bg_processes[i].pid);
            }

            for(int j=i; j<num_bg_proc-1; j++){
                bg_processes[j] = bg_processes[j+1];
            }
            num_bg_proc--;
            i--; // accounting for the process that has just been removed
        }
    }
}

void execute_foreground(char *command, char *args[1024], int size){
    time_t starttime, endtime;
    time(&starttime);

    // printf("Entered foreground process");
    // printf("Foreground -%s-", command);


    // adding all the custom process to 

    if(chooseprocess(command, args, size) == 1){
        return;
    }

    if(strcmp(command, "\n") == 0){
        return;
    }

    pid_t pid = fork();
    // printf("Yash here");
    
    // printf("%s\n", command);
    if(pid == 0){
        // Child process
        int ret = execvp(command, args);
        if(ret == -1){
            perror("execvp");
            exit(EXIT_FAILURE);
        }

    }else{
        // Parent process

        waitpid(pid, NULL, 0);
        time(&endtime);
        int exec_time = (int)difftime(endtime, starttime);

        if(exec_time > 2){
            printf("Foreground process %s took %d seconds\n", command, exec_time);
        }
    }
}

void execute_background(char *command, char *args[1024], int size){


    // printf("Entered the background process");
    pid_t pid2 = fork();
    if(strcmp(command, "\n") == 0){
        return;
    }
    //printf("%s",command);
    if(pid2 == 0){
        // Child process 
        // printf("Entered the child process");
        setpgid(0, 0);
        int ret = execvp(command, args);
        if(ret == -1){
            perror("execvp");
            exit(EXIT_FAILURE);
        }

    }else if(pid2 > 0){
        // Parent process
        // printf("I m herer");
        printf("%d\n", pid2);

        printf("No of background processes before %d\n", num_bg_proc);
        
        if(num_bg_proc < MAX_BACKGROUND){
            bg_processes[num_bg_proc].pid = pid2;
            bg_processes[num_bg_proc].command = strdup(command);
            num_bg_proc++;
        }

        printf("NO of background processes %d\n", num_bg_proc);
    }
    // }else{
    //     perror("Fork error in Background process");
    // }

    
}