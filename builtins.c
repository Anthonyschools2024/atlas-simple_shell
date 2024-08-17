#include "shell.h"

/**
 * handle_exit - Handles the exit command
 * @args: The arguments for the command
 */

void handle_exit(char **args, int last_status)
{
	if (args) /* Ensure memory freed on exit */
	{
		free(args);
		args = NULL;
	}
	exit(last_status);
}

/**
 * handle_env - Handles the env command
 * @args: The arguments for the command
 */

void handle_env(char **args)
{
	int i; /* Iteration var */

	for (i = 0; environ[i] != NULL; i++) /* For each env in environ print environ */
	{
		printf("%s\n", environ[i]);
	}

	if (args) /* Ensure args memory is freed */
	{
		free(args);
		args = NULL;
	}
}