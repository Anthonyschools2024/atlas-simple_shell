#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

extern char **environ;

void prompt(void);
char *read_line(void);
char **split_line(char *line);
int execute(char **args);
void shell_loop(void);
void handle_exit(char **args, int last_status);
void handle_env(char **args);
void handle_man(void);
int _strcmp(const char *s1, const char *s2);

#endif