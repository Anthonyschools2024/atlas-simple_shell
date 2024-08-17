#include "shell.h"

/**
 * execute - Executes a command
 * @args: The arguments for the command
 *
 * Return: 1 if the shell should continue running, 0 if it should terminate
 */

int execute(char **args)
{
	pid_t pid;	/* Process ID variable */
	int status; /* Status integer */

	if (args[0] == NULL) /* Args null check */
		return (1);

	pid = fork(); /* PID becomes forked ID, start new process */

	if (pid == 0) /* Child process execution */
	{
		if (execvp(args[0], args) == -1)
		{
			perror("execvp");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0) /* Error handling */
	{
		perror("fork");
	}
	else /* If it gets here, code is running in Parent */
	{
		do
		{
			waitpid(pid, &status, WUNTRACED); /* Wait for child with PID to finish */
		} while (!WIFEXITED(status) && !WIFSIGNALED(status)); /* Loop ends if child ends or was terminated */
	}

	return (1); /* Return success */
}