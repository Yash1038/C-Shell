#include "../include/headers.h"


char check = 0; // For checking if the shell is started at that point or not

void getUserDet(){
    
    if(gethostname(hostName, 255) == -1) {
        perror("gethostname");
        exit(EXIT_FAILURE);
    }

    // printf("<%s> ", hostName);

    // Getting username as well


    if(getlogin_r(userName, 255) == -1) {
        perror("getlogin_r");
        exit(EXIT_FAILURE);
    }

    // Setting up the pwd


    if(getcwd(pwd, 255) == NULL) {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }

    strncpy(homedir, pwd, 255);

    check = 1;

}

void prompt() {
    
    if(check == 0){
        getUserDet();
    }


    if(getcwd(pwd, 255) == NULL) {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }

    if(strncmp(pwd, homedir, strlen(homedir)) == 0){
        int temp_len = strlen(homedir);
        char temp_pwd[255];
        strncpy(temp_pwd, pwd+temp_len, 255);
        // printf(BOLD GREEN "<%s@%s:~%s> " RESET, userName, hostName, temp_pwd);
        // printf(BOLD GREEN "<%s@%s:~%s> " RESET, userName, hostName, temp_pwd);
        printf(BOLD GREEN "<%s@%s:" RESET BOLD BLUE "~%s> " RESET, userName, hostName, temp_pwd );
    }else{
        // printf(BOLD GREEN "<%s@%s:%s> " RESET, userName, hostName, pwd);
        printf(BOLD GREEN "<%s@%s:" RESET BOLD BLUE "%s> " RESET, userName, hostName, pwd );
        
    }

}
