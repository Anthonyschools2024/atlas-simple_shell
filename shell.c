#include "shell.h"

/**
 * shell_loop - Main loop of the shell
 */

void shell_loop(void)
{
	/*
	 * Params:
	 * *line: A character pointer to hold the user entry line after using read_line method
	 * **args: A character pointer to hold the tokenized line after using split_line method
	 * status: Holds a default status code for error handling
	 */

	char *line;
	char **args;
	int status = 1;
	int last_status = 0;

	do /* A Do / While loop is created to be the main loop of the console. */
	{
		prompt();			/* The user is prompted for input via prompt method */
		line = read_line(); /* Stores user input via read_line to the line var */
		if (line == NULL)	/* Check if the user gave input */
		{
			if (isatty(STDIN_FILENO))
			{
				printf("\n"); /* Print newline if no input passed */
			}
			exit(last_status);
		}
		args = split_line(line); /* Store tokenized input (via split_line) in the args var */
		if (args[0] == NULL)	 /* Null check for args */
		{
			free(line); /* Free memory */
			free(args);
			continue;
		}
		if (_strcmp(args[0], "exit") == 0) /* Check if user enters "exit" */
		{
			free(line);						/* Free memory */
			handle_exit(args, last_status); /* Exit Shell via handle_exit */
		}
		else if (_strcmp(args[0], "env") == 0) /* Check if user enters "env" */
		{
			handle_env(args); /* Prints current ENV via handle_env */
			free(line);		  /* Free memory */
			free(args);
		}
		else if (_strcmp(args[0], "man") == 0) /* Check if user enters "man" */
		{
			handle_man(); /* Brings up the man page via handle_man */
			free(line);	  /* Free memory */
			free(args);
		}
		else
		{
			last_status = execute(args); /* Execute user input via execute method */
			free(line);					 /* Free memory after execution */
			free(args);
		}
	} while (status); /* While status var is not null, do / while loop persists */

	if (line) /* Doublecheck that line memory is freed */
	{
		free(line);
		line = NULL;
	}
	if (args) /* Doublecheck that args memory is freed */
	{
		free(args);
		args = NULL;
	}
}