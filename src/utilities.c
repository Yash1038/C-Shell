#include "../include/headers.h"


void replaceAmpersand(char *str) {
    char result[1000];  // You can adjust the size as needed
    int resultIndex = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '&') {
            result[resultIndex++] = '&';
            // result[resultIndex++] = ' ';
            result[resultIndex++] = ';';
        } else {
            result[resultIndex++] = str[i];
        }
    }

    result[resultIndex] = '\0';  // Null-terminate the result

    strcpy(str, result);  // Copy the modified result back to the original string
}

// replacing substring a with c in b

void replaceSubstring(char *a, char *b, char *c){
    char *pos = strstr(b, a);

    if(pos != NULL){
        int c_length = strlen(c);
        int tail_length = strlen(pos + replace);

        int len_diff = c_length - replace;

        memmove(pos + c_length, pos + replace, tail_length + 1);

        memcpy(pos, c, c_length);

        memmove(pos + c_length, pos + c_length + len_diff, strlen(pos + c_length + len_diff) + 1);
    }
}

int compare_f_w_s(char *filename, char *string){

    int length = strlen(filename);

    for(int i = length - 1; i >= 0; i--){
        if(filename[i] == '.'){
            filename[i] = '\0';
            break;
        }
    }

    int result = strcmp(filename, string);

    return result;
}

char *rel_path(char *file, char *working_dir){
    // Given the path to a file
    // Given the path to the workign directory 

    // Give out the relative path to the file from the working directory

    // start coding

    char *rel_path = (char *)malloc(255 * sizeof(char));

    int file_length = strlen(file);
    int working_dir_length = strlen(working_dir);

    for(int i = 0; i < file_length; i++){
        if(i < working_dir_length){
            continue;
        }
        else{
            rel_path[i - working_dir_length] = file[i];
        }
    }
    rel_path[file_length - working_dir_length] = '\0';

    return rel_path;
}