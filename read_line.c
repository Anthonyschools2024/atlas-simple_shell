#include "shell.h"

/**
 * read_line - Reads a line of input from the user
 *
 * Return: Returns the input line
 */

char *read_line(void)
{
	char *line = NULL;	/* Empty var to hold user input and return */
	size_t bufsize = 0; /* Adjustable var to set size of memory for user input */

	if (getline(&line, &bufsize, stdin) == -1) /* If there is an error, free memory and return NULL */
	{
		free(line);
		return (NULL);
	}
	return (line); /* Return user input */
}