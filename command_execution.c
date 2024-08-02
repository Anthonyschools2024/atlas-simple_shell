#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "main.h"

void shell_command(char **args) {
        pid_t CDPR = fork();
        char *path;

        path = search_path(args[0]);
        /* Child process */
        
        if (CDPR == 0) {
        
                if (execve(path, args, NULL) == -1) {
                        perror("execve");
                        free(path);
                        exit(EXIT_FAILURE);
                }
        } else if (CDPR < 0) {
                perror("fork");
                free(path);
                exit(EXIT_FAILURE);
        } else {
                free(path);
                wait(NULL);
                /* Parent process waiting for child */
        }

}
