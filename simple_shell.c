#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#define BUFFER_SIZE 1024
#define MAX_ARGS 32

void tokenize_input(char *buffer, char *args[]);
int execute_command(char *args[], int num_args);

/**
 * tokenize_input -  Tokenizes input into separate arguments
 *
 * @buffer: input string to be tokenized
 * @args: array of strings where tokens will be stored
 */

void tokenize_input(char *buffer, char *args[])
{
	char *token = strtok(buffer, " ");
	int i = 0;

	while (token != NULL && i < MAX_ARGS - 1)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
}


/**
 * execute_command - Executes built-in commands or external programs entered by the user
 *
 * @args: array of command arguments
 * @num_args: number of arguments
 *
 * Return: 0 if a built-in command was executed, 1 otherwise
 */

int execute_command(char *args[], int num_args)
{
	if (strcmp(args[0], "cd") == 0)
	{
		if (num_args == 2)
		{
			if (chdir(args[1]) != 0)
			{
				perror("chdir");
			}
	}
	else
	{
		fprintf(stderr, "Usage: cd <directory>\n");
	}
	return (0);
	}
	else if (strcmp(args[0], "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}
	return (1);
}

   

  
	        