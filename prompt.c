#include "shell.h"

/**
 * prompt - Displays the shell prompt
 */

void prompt(void)
{
	/**
	 * Prompt method uses the "isatty" with STDIN_FILENO to check if the console is using the default input file,
	 * If TRUE it prints the user prompt
	 */

	if (isatty(STDIN_FILENO))
	{
		printf("($) ");
	}
}