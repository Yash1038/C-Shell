#ifndef HEADERS_H_
#define HEADERS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <time.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>
#include <sys/select.h>
#include <sys/sysinfo.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>
#include <pthread.h>



// Color Codes

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define BLUE "\033[0;34m"
#define RESET "\033[0m"
#define YELLOW "\033[0;33m"
#define CYAN "\033[0;36m"
#define MAGENTA "\033[0;35m"
#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"
#define BLACK "\033[0;30m"
#define WHITE "\033[0;37m"

char hostName[255];
char userName[255];
char pwd[255];
char homedir[255];
char prevdir[255];
char addCmd[4096];
char temp[4096];
int pastid;
int run;
int replace;
int seek_count;
int num_bg_proc;

void prompt();
void super_process(char *input);
void input_process(char *inp_pro);
int chooseprocess(char *command, char *args[1024], int size);
void execute_foreground(char *command, char *args[1024], int size);
void execute_background(char *command, char *args[1024], int size);
void check_bg_process();
void peek(char *pwd);
void peek_a(char *pwd);
void peek_l(char *pwd);
void peek_al(char *pwd);
void proclore(pid_t id);
void replaceAmpersand(char *input);
void replaceSubstring(char *a, char *b, char *c);
void seek(char *pwd, char *filename, char *orig_dir);
int compare_f_w_s(char *filename, char *string);
char *rel_path(char *file, char *working_dir);
void seek_d(char *pwd, char *filename, char *orig_dir);
void seek_f(char *pwd, char *filename, char *orig_dir);
void seek_ef(char *pwd, char *filename, char *orig_dir, char *seek_temp_path);
void seek_ed(char *pwd, char *filename, char *orig_dir, char *seek_temp_path);
void iMan(char *command);
void piping_init(char *input, int background);
void command_split(char *inp_pro, int background);
void activities();
void old_code(char *input);

#include "prompt.h"
#endif