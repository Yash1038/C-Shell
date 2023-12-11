// this is how you choose process
#include "../include/headers.h"

void piping_init(char *inp_string, int background){
    char *inp_string_dup = strdup(inp_string);
    // char *command = strtok(inp_string_dup, "\n\r\v\f\t");
    // printf("%s\n", command);

    // suppose a string is uasdkhgasuhgd | kjsadhgasd | asdjhgalsjd
    // we split it into 3 parts

    char *pipargs[1024];
    int no_of_pipes = 0;
    char *token = strtok(inp_string, "|");
    while(token != NULL){
        pipargs[no_of_pipes] = token;
        token = strtok(NULL, "|");
        no_of_pipes++;
    }
    
    // printf("%d\n", no_of_pipes);
    // return;
    // now comes the piping bullshit

    int prev_pipe[2];
    int curr_pipe[2];
    int fd_inp = STDIN_FILENO;

    for(int i = 0; i < no_of_pipes; i++){
        if(i < no_of_pipes - 1){
            pipe(curr_pipe);
        }
        else{
            curr_pipe[0] = -1;
            curr_pipe[1] = -1;
        }

        if(fd_inp != STDIN_FILENO){
            dup2(fd_inp, STDIN_FILENO);
            close(fd_inp);
        }

        if(curr_pipe[1] != STDOUT_FILENO){
            dup2(curr_pipe[1], STDOUT_FILENO);
            close(curr_pipe[1]);
        }

        // input_process(pipargs[i]);
        command_split(pipargs[i], background);

        close(curr_pipe[1]);

        if(fd_inp != STDIN_FILENO){
            close(fd_inp);
        }

        fd_inp = curr_pipe[0];
    }

    return;

}

void command_split(char *inp_pro, int background){

    // printf("%s\n", inp_pro);


    char *inp_pro_dup = strdup(inp_pro);
    char *command = strtok(inp_pro_dup, "\n\r\v\f\t");
    replace = strlen(inp_pro);

    char *temp = strtok(inp_pro_dup, " ");
    if(temp != NULL){
        command = temp;
    }



    char *args[1024];
    int i = 0;
    char *token = strtok(inp_pro, " \n\v\f\r\t");
    while(token != NULL){
        args[i] = token;
        token = strtok(NULL, " \n\v\f\r\t");
        i++;
    }
    args[i] = NULL;


    /////////////////////////////////

    if(strcmp(command, "exit") == 0 || strcmp(command, "quit") == 0){
        // printf("Bye! %d \n", getpid());
        run = 0;
        // exit(0);
        return;
    }
    
    
    if(background == 1){
        // printf("background process\n");
        // args[i-1] = NULL;
        // background = 1;
        execute_background(command, args, i);
    }else{
        // printf("foreground process\n");
        execute_foreground(command, args, i);
    }

    ///
}

void input_process(char *inp_pro){

    // printf("%s\n", inp_pro);


    char *inp_pro_dup = strdup(inp_pro);
    char *final = strdup(inp_pro);
    char *command = strtok(inp_pro_dup, "\n\r\v\f\t");
    replace = strlen(inp_pro);
    int background = 0;

    // printf("%s\n", inp_pro_dup);
    // return;

    char *temp = strtok(inp_pro_dup, " ");
    if(temp != NULL){
        command = temp;
    }



    char *args[1024];
    int i = 0;
    char *token = strtok(inp_pro, " \n\v\f\r\t");
    while(token != NULL){
        args[i] = token;
        token = strtok(NULL, " \n\v\f\r\t");
        i++;
    }
    args[i] = NULL;

    // printf("%s", command);

    // chooseprocess(command, args, i);
    // if the last word is &, it should be a background process
    // otherwise it should be a foreground process


    /////////////////////////////////

    if(strcmp(command, "exit") == 0 || strcmp(command, "quit") == 0){
        // printf("Bye! %d \n", getpid());
        run = 0;
        // exit(0);
    }

    if(strcmp(args[i-1], "&") == 0){
        // printf("background process\n");
        args[i-1] = NULL;
        background = 1;
        // execute_background(command, args, i-1);
    }else{
        // printf("foreground process\n");
        // execute_foreground(command, args, i);
    }

    // find the last occurence of & in the string and replace it with \0

    char *temp2 = strrchr(final, '&');
    if(temp2 != NULL){
        if(strcmp(temp2, "&") == 0 && background == 1){
            replace = strlen(final) - strlen(temp2);
            final[replace] = '\0';
        }
    }

    // printf("%s\n", final);
    piping_init(final, background);


    /////////////////////////////////
    return;
}

void old_code(char *inp_pro){

    // printf("%s", inp_pro);


    char *inp_pro_dup = strdup(inp_pro);
    char *command = strtok(inp_pro_dup, "\n\r\v\f\t");
    replace = strlen(inp_pro);



    char *temp = strtok(inp_pro_dup, " ");
    if(temp != NULL){
        command = temp;
    }


    char *args[1024];
    int i = 0;
    char *token = strtok(inp_pro, " \n\v\f\r\t");
    while(token != NULL){
        args[i] = token;
        token = strtok(NULL, " \n\v\f\r\t");
        i++;
    }
    args[i] = NULL;

    // printf("%s", command);

    // chooseprocess(command, args, i);
    // if the last word is &, it should be a background process
    // otherwise it should be a foreground process


    /////////////////////////////////

    if(strcmp(command, "exit") == 0 || strcmp(command, "quit") == 0){
        // printf("Bye! %d \n", getpid());
        run = 0;
        // exit(0);
    }
    else if(strcmp(args[i-1], "&") == 0){
        // printf("background process\n");
        args[i-1] = NULL;
        execute_background(command, args, i-1);
    }else{
        // printf("foreground process\n");
        execute_foreground(command, args, i);
    }

    /////////////////////////////////
    return;
}

int chooseprocess(char *command, char *args[1024], int size){

    int flag = 0;


    if(strcmp(command, "pastevents") == 0){
        // printf("Hi\n");
        // pastid = 1;
        flag = 1;

        // open the file past_commands.txt in homedir
        
        char *fileadd = (char *)malloc(255 * sizeof(char));
        strcpy(fileadd, homedir);
        strcat(fileadd, "/past_commands.txt");

        FILE *fp;
        fp = fopen(fileadd, "r");

        // if size is 1, then print all the past events

        if(size == 1){
            pastid = 1;
            char *line = NULL;
            size_t len = 0;
            ssize_t read;
            while((read = getline(&line, &len, fp)) != -1){
                printf("%s", line);
            }
            fclose(fp);
            return 1;
        }

        // if size is 2, and second argument is purge, then erase contents in the file

        else if(size == 2 && strcmp(args[1], "purge") == 0){
            fclose(fp);
            fp = fopen(fileadd, "w");
            fclose(fp);
            pastid = 1;
            return 1;
        }

        // if size is 3, and is of form pastevents execute <index>, then print the command at that index from the bottom of that file
        // the index is supposed to be from the bottom of the file

        else if(size == 3 && strcmp(args[1], "execute") == 0){
            pastid = 1;
            int index = atoi(args[2]);
            char *line = NULL;
            size_t len = 0;
            ssize_t read;
            int count = 0;
            while((read = getline(&line, &len, fp)) != -1){
                count++;
            }
            fclose(fp);
            fp = fopen(fileadd, "r");
            if(index > count){
                printf("Index out of bounds\n");
                fclose(fp);
                return 1;
            }
            int count2 = 0;
            while((read = getline(&line, &len, fp)) != -1){
                count2++;
                if(count2 == count - index + 1){
                    // replaceSubstring("pastevents", temp, line);
                    // printf("%s \n", temp);
                    // printf("%s", line);
                    super_process(line);
                    // flag = 1;
                    // add that line to the addCmd string
                    // strcat(addCmd, line);
                    // printf("%s", line);
                    break;
                    return 1;
                }
            }
            fclose(fp);
            return 1;
        }

    }


    // implementing cd

    else if(strcmp(command, "warp") == 0){
        // printf("hello doing cd");
        for(int j = 1; j < size; j++){
            // printf("%s\n", args[j]);
            // strcpy(prevdir, pwd);
            if(strcmp(args[j], "-") == 0){
                char temp[255];
                strcpy(temp, pwd);
                chdir(prevdir);
                strcpy(prevdir, temp);
            }else if(strcmp(args[j], "~") == 0){
                // strcpy(prevdir, pwd);
                getcwd(prevdir, 255);
                chdir(homedir);
            }else{
                // strcpy(prevdir, pwd);
                getcwd(prevdir, 255);
                if(chdir(args[j]) == -1){
                    perror("Warp");
                }
                // chdir(args[j]);
            }
            // getcwd(prevdir, 255);
            // printf("%s",prevdir);
            // printf("%s",pwd);
            // chdir(args[j]);
        }
        flag = 1;
    
    }

    else if(strcmp(command, "proclore") == 0){
        // get the process id of the shell

        if(size == 1){
            // printf("hello");
            pid_t shell_pid = getpid();
            proclore(shell_pid);
        }else{
            pid_t shell_pid = atoi(args[1]);
            if(shell_pid == 0){
                perror("Invalid pid");
                return 1;
            }
            proclore(shell_pid);
        }

        flag = 1;
    }

    else if(strcmp(command, "peek") == 0){
        // this is nothing but ls
        // storing pwd in a special string

        // create a temp string and store the pwd string in that 
        // char temp[255];
        // strcpy(temp, pwd);
        // add /include to pwd
        // strcat(temp, "/include");

        if(size == 1){
            // this is basic case of ls in same directory
            // printf("%s", pwd);
            peek(pwd);
            flag = 1;
        }

        else if(strcmp(args[1], "-a") == 0){
            // this is ls -a

            if(size == 2){
                // ls -a
                peek_a(pwd);
            }
            if(size == 3){
                if(strcmp(args[1], "-l") == 0){
                    // ls -a -l
                    peek_al(pwd);
                }else{
                    // ls -a <some directory>
                    if(chdir(args[2]) == -1){
                        printf("No such directory exists\n");
                        return 1;
                    }
                    // chdir(args[2]);
                    char pwd_temp[255];
                    getcwd(pwd_temp, 255);
                    peek_a(pwd_temp);
                    chdir(pwd);
                }
            }
            if(size == 4){
                // ls -a -l <some dir>
                if(chdir(args[3]) == -1){
                    printf("No such directory exists\n");
                    return 1;
                }
                // chdir(args[2]);
                char pwd_temp[255];
                getcwd(pwd_temp, 255);
                peek_al(pwd_temp);
                chdir(pwd);
            }

            flag = 1;

            
        }

        else if(strcmp(args[1], "-l") == 0){
            // this is ls -l
            if(size == 2){
                // ls -l
                peek_l(pwd);
            }
            if(size == 3){
                if(strcmp(args[1], "-a") == 0){
                    // ls -l -a
                    peek_al(pwd);
                }else{
                    // ls -l <some directory>
                    if(chdir(args[2]) == -1){
                        printf("No such directory exists\n");
                        return 1;
                    }
                    // chdir(args[2]);
                    char pwd_temp[255];
                    getcwd(pwd_temp, 255);
                    peek_l(pwd_temp);
                    chdir(pwd);
                }
            }
            if(size == 4){
                // ls -l -a <some dir>
                if(chdir(args[3]) == -1){
                    printf("No such directory exists\n");
                    return 1;
                }
                // chdir(args[2]);
                char pwd_temp[255];
                getcwd(pwd_temp, 255);
                peek_al(pwd_temp);
                chdir(pwd);
            }

            flag = 1;
        }

        else if(strcmp(args[1], "-al") == 0 || strcmp(args[1], "-la") == 0){
            // this is ls -al
            if(size == 3){
                // ls -al <some dir>
                if(chdir(args[2]) == -1){
                    printf("No such directory exists\n");
                    return 1;
                }
                // chdir(args[2]);
                char pwd_temp[255];
                getcwd(pwd_temp, 255);
                peek_al(pwd_temp);
                chdir(pwd);
                return 1;
            }
            else{
                // ls -al
                peek_al(pwd);
                return 1;
            }
        }

        else{
            // // this is ls <some dir>
            if(chdir(args[1]) == -1){
                printf("No such directory exists\n");
                return 1;
            }
            // chdir(args[1]);
            char pwd_temp[255];
            getcwd(pwd_temp, 255);
            peek(pwd_temp);
            chdir(pwd);
            return 1;
        }

        flag = 1;
    }

    else if (strcmp(command, "seek") == 0){

        if(size == 2){
            seek(pwd, args[1], pwd);
        }

        if(size == 3){
            if(strcmp(args[1], "-d") == 0){
                seek_d(pwd, args[2], pwd);
            }

            else if(strcmp(args[1], "-f") == 0){
                seek_f(pwd, args[2], pwd);
            }

            else{

                // seek input_file target_directory
                if(chdir(args[2]) == -1){
                    printf("No such directory exists\n");
                    return 1;
                }
                // chdir(args[2]);
                char pwd_temp[255];
                getcwd(pwd_temp, 255);
                seek(pwd_temp, args[1], pwd_temp);
                chdir(pwd);


            }

        }

        if(size == 4){
            if(strcmp(args[1], "-d") == 0){
                // seek -d input_directory target_directory
                if(chdir(args[3]) == -1){
                    printf("No such directory exists\n");
                    return 1;
                }
                char pwd_temp[255];
                getcwd(pwd_temp, 255);
                seek_d(pwd_temp, args[2], pwd_temp);
                chdir(pwd);

            }

            if(strcmp(args[1], "-f") == 0){
                // seek -f input_file target_directory
                if(chdir(args[3]) == -1){
                    printf("No such directory exists\n");
                    return 1;
                }
                char pwd_temp[255];
                getcwd(pwd_temp, 255);
                seek_f(pwd_temp, args[2], pwd_temp);
                chdir(pwd);
            }

            if(strcmp(args[1], "-e") == 0){
                if(strcmp(args[2], "-d") == 0){
                    // seek_ed(pwd, args[3], pwd);
                    // seek -e -d input_directory
                    
                    seek_count = 0;
                    char *seek_temp_path = (char *)malloc(255*sizeof(char));
                    seek_ed(pwd, args[3], pwd, seek_temp_path);

                    if(seek_count == 1){
                        printf("%s\n", seek_temp_path);
                        chdir(seek_temp_path);

                        // return 1;
                    }
                    else{
                        printf("No such directory exists\n");
                        return 1;
                    }

                }
                
                if(strcmp(args[2], "-f") == 0){

                    // seek_ed(pwd, args[3], pwd);
                    // seek -e -f input_file
                    seek_count = 0;
                    char *seek_temp_path = (char *)malloc(255*sizeof(char));
                    seek_ef(pwd, args[3], pwd, seek_temp_path);

                    if(seek_count == 1){
                        printf("%s\n", seek_temp_path);

                        // now open the file
                        FILE *fp = fopen(seek_temp_path, "r");
                        if(fp == NULL){
                            printf("Error opening file\n");
                            // return 1;
                        }

                        char ch;
                        while((ch = fgetc(fp)) != EOF){
                            printf("%c", ch);
                        }

                        printf("\n");

                        fclose(fp);
                    }
                    else{
                        printf("No such file exists\n");
                    }


                }
            }
        }

        if(size == 5){
            if(strcmp(args[1], "-e") == 0){
                if(strcmp(args[2], "-d") == 0){
                    // seek -e -d input_directory target_directory

                    if(chdir(args[4]) == -1){
                        printf("No such directory exists\n");
                        return 1;
                    }

                    char pwd_temp[255];
                    getcwd(pwd_temp, 255);
                    seek_count = 0;
                    char *seek_temp_path = (char *)malloc(255*sizeof(char));
                    seek_ed(pwd_temp, args[3], pwd_temp, seek_temp_path);

                    if(seek_count == 1){
                        printf("%s\n", seek_temp_path);
                        chdir(seek_temp_path);
                        // return 1;
                    }
                    else{
                        printf("No such directory exists\n");
                        // return 1;
                    }
                }

                if(strcmp(args[2], "-f") == 0){
                    // seek -e -f input_file target_directory

                    if(chdir(args[4]) == -1){
                        printf("No such directory exists\n");
                        return 1;
                    }

                    char pwd_temp[255];
                    getcwd(pwd_temp, 255);
                    seek_count = 0;
                    char *seek_temp_path = (char *)malloc(255*sizeof(char));
                    seek_ef(pwd_temp, args[3], pwd_temp, seek_temp_path);

                    if(seek_count == 1){
                        printf("%s\n", seek_temp_path);

                        // now open the file
                        FILE *fp = fopen(seek_temp_path, "r");
                        if(fp == NULL){
                            printf("Error opening file\n");
                            // return 1;
                        }

                        char *line = NULL;
                        size_t len = 0;
                        ssize_t read;

                        while((read = getline(&line, &len, fp)) != -1){
                            printf("%s", line);
                        }
                        printf("\n");

                        fclose(fp);
                    }
                    else{
                        printf("No such file exists\n");
                    }

                    chdir(pwd);


                }
            }
        }

        flag = 1;

    }
    
    else if (strcmp(command, "seek") == 0){
        seek_count = 0;
        char *seek_temp_path = (char *)malloc(255*sizeof(char));
        seek_ef(pwd, args[1], pwd, seek_temp_path);
        // printf("%s\n", seek_temp_path);
        
        // // seek_ef(pwd, args[1], pwd);
        // printf("%d", seek_count);
        // printf("%s", seek_temp_path);
        if(seek_count == 1){
            printf("%s\n", seek_temp_path);

            // now open the file and print the contents

            FILE *fp;
            char ch;
            fp = fopen(seek_temp_path, "r");
            if(fp == NULL){
                printf("File not found\n");
                return 1;
            }

            while((ch = fgetc(fp)) != EOF){
                printf("%c", ch);
            }
            printf("\n");

            fclose(fp);
        }
        // seek_ef(pwd, args[1], pwd);
        // printf("%d", seek_count);

        flag = 1;
    }

    else if( strcmp(command, "iMan") == 0){

        // printf("%s \n", args[1]);

        iMan(args[1]);
        flag = 1;
    }

    else if(strcmp(command, "activities") == 0){

        activities();
        flag = 1;
    }
    

    return flag;
}