[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/76mHqLr5)

# Description

### This is a basic C shell with a few implemented commands

##### Warp: `cd` to a directory using a nickname

##### peek: `ls` a directory using a nickname

##### pastevents: stores `history` of commands

##### seek: finds a file in the given directory and its subtree

##### proclore: Gives the status of a process given its pid

##### iMan : Gives details of a given command (if available). For example : `iMan ls`

##### The shell has pipelining and I/O redirection implemented in itself. For example : `ls | grep a > b.txt`

##### The shell can also run both foreground and background processes. For example : `ls &`

##### Activities: This command gives status of all the running processes.

##### Commands such as seek, peek, ls has various flags implemented such as -a, -l, etc. 



# Assumptions


##### 1. The maximum number of arguments in a single command will not exceed 255
##### 2. The maximum number of background processes at any time is less than or equal to 100
##### 3. It is assumed that the special characters such as `|`, `>`, `<`, `&` will not be used in the arguments of the commands


# How to run

##### 1. Clone the repository
##### 2. Run `make` in the directory
##### 3. Run `./final` to start the shell
