#include "shell.h"

/**
 * split_line - Splits a line into tokens
 * @line: The input line from read_line
 *
 * Return: Returns an array of tokens
 */

char **split_line(char *line)
{
	/*
	 * Params:
	 * bufsize: Sets a standard size to hold tokens
	 * position: An iteration var to move through the tokens array
	 * tokens: Reserves memory for tokenized user input
	 * token: Variable to hold individual tokens
	 */

	int bufsize = 64;
	int position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens) /* Null check for tokens memory allocation */
	{
		fprintf(stderr, "Allocation Error\n"); /* Print error */
		free(line);							   /* Free memory */
		exit(EXIT_FAILURE);					   /* Exit with error */
	}

	token = strtok(line, " \t\r\n\a"); /* Separate user input into tokens, set delimiters */

	while (token != NULL) /* Start iterative action to fill tokens array */
	{
		tokens[position] = token; /* Current position of tokens array is assigned current token */
		position++;				  /* Increment */

		if (position >= bufsize) /* If tokens position exceeds set bufsize, increase bufsize */
		{
			bufsize += 64;										/* Add to bufsize var */
			tokens = realloc(tokens, bufsize * sizeof(char *)); /* Reallocate memory */
			if (!tokens)										/* Null check after reallocation */
			{
				fprintf(stderr, "Allocation Error"); /* Print error */
				free(line);							 /* Free memory */
				exit(EXIT_FAILURE);					 /* Exit with error */
			}
		}
		token = strtok(NULL, " \t\r\n\a"); /* Set subsequent calls to strtok */
	}
	tokens[position] = NULL; /* Null data at the end of the tokens array */
	return (tokens);		 /* Return tokenized input */
}