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

   
/**
 * sigint_handler - Handles the SIGINT signal (Ctrl+C)
 *
 * @signum: Signal Number
 */

void sigint_handler(int signum)
{
	(void)signum;
	printf("\nCaught SIGINT (Crtl+C)\n");
}


/**
 * sigtstp_handler - Handles the SIGTSTP signal (Ctrl+Z)
 *
 * @signum: Signal Number
 */

void sigtstp_handler(int signum)
{
	(void)signum;
	printf("\nCaught SIGSTP (Ctrl+Z)\n");
}
  

/**
 * main - Entry point for Simple Shell program
 *
 * @argc: Number of command line arguments
 * @argv: Array of command line arguments
 * @env: Array of environment variables
 *
 * Return: EXIT_SUCESS
 */

int main(int argc, char **argv, char **env)
{
	char buffer[BUFFER_SIZE];
	char *args[MAX_ARGS];
	pid_t child_pid;
	int status;

	(void)argc;
	(void)argv;

	signal(SIGINT, sigint_handler);
	signal(SIGTSTP, sigtstp_handler);

	while (1)
	{
		printf("$ ");
		fflush(stdout);

		if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
		{
			printf("\n");
			break;
		}

		buffer[strcspn(buffer, "\n")] = '\0';

		tokenize_input(buffer, args);

		child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (child_pid == 0)
		{
			execve(args[0], args, env);
			fprintf(stderr, "Failed to execute %s: %s\n", args[0], strerror(errno));
			exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(child_pid, &status, 0);
		}
	}
	return (EXIT_SUCCESS);
}	        