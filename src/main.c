#include "../include/headers.h"

void super_process(char *input){
    replaceAmpersand(input);

    char *command = strtok(input, ";");
    char *args[1024];
    int i = 0;
    while (command != NULL)
    {
        args[i] = command;
        command = strtok(NULL, ";");
        i++;
    }

    for (int j = 0; j < i; j++)
    {
        // printf("%s\n", args[j]);
        if(run == 0){
            break;
        }
        input_process(args[j]);
        // piping(args[j]);
        // old_code(args[j]);
        getcwd(pwd, 255);

    }

}



int main()
{

    // Create a text-file named past_commands.txt if it doest exists

    FILE *fp;
    fp = fopen("past_commands.txt", "a");
    fclose(fp);
    run = 1;
    num_bg_proc = 0;

    // Keep accepting commands
    while (run == 1)
    {
        // strcpy(prevdir, pwd);
        pastid = 0;

        prompt();
        char input[4096];
        fgets(input, 4096, stdin);

        // char temp[4096];
        strcpy(temp, input);
        // printf("%s", input);

        replaceAmpersand(input);
        // printf("%s", input);

        // splitting the input w.r.t ; Thus getting multiple sets of commands

        super_process(input);

        if(pastid == 0){

            char *fileadd = (char *)malloc(255 * sizeof(char));
            strcpy(fileadd, homedir);
            strcat(fileadd, "/past_commands.txt");

            fp = fopen(fileadd, "a");
            fprintf(fp, "%s", temp);
            fclose(fp);


            // count the number of lines in the file
            fp = fopen(fileadd, "r");
            char ch;
            int countlines = 0;
            while(!feof(fp)){
                ch = fgetc(fp);
                if(ch == '\n'){
                    countlines++;
                }
            }
            fclose(fp);


            // printf("%d \n", countlines);

            if(countlines > 15){
                // create a temp file
                FILE *tempfile = tmpfile();
                // copy all the lines from 2nd line
                fp = fopen(fileadd, "r");
                char *line = NULL;
                size_t len = 0;
                ssize_t read;
                int i = 0;
                while((read = getline(&line, &len, fp)) != -1){
                    if(i != 0){
                        fprintf(tempfile, "%s", line);
                    }
                    i++;
                }
                fclose(fp);

                // copy all the lines from temp file to past_commands.txt
                fp = fopen(fileadd, "w");
                fseek(tempfile, 0, SEEK_SET);
                while((read = getline(&line, &len, tempfile)) != -1){
                    fprintf(fp, "%s", line);
                }

                fclose(fp);
                fclose(tempfile);


            }
        





            // fclose(fp);

            free(fileadd);

        } 

        // printf("%s \n", temp);

        check_bg_process();


        
    }

}
