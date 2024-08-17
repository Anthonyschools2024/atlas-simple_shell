#include "shell.h"

/**
 * handle_man - Displays the shell manual
 */
void handle_man(void)
{
	FILE *file = fopen("man", "r");
	char ch;

	if (file == NULL)
	{
		perror("Error opening man file");
		return;
	}

	while ((ch = fgetc(file)) != EOF)
	{
		putchar(ch);
	}

	fclose(file);
}