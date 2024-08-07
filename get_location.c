#include "shell.h"
/**
 * get_location - Retrieve the full path of a command executable.
 * @command: The command name.
 *
 * Description: This function searches for the full path of a command executable
 * by checking directories listed in the PATH environment variable.
 * 
 * Return: A pointer to the location of the command if found, otherwise NULL
 */
char *get_location(char *command)
{
	char *path, *path_copy, *path_token, *file_path;
	int command_length, directory_length;
	struct stat buffer;

	path = _getenv("PATH");

	if (path)
	{
		path_copy = _strdup(path);
		if (path_copy == NULL)
			return (NULL);
		command_length = strlen(command);

		path_token = strtok(path_copy, ":");

		while (path_token != NULL)
		{
			directory_length = strlen(path_token);
			file_path = malloc(command_length + directory_length + 2);
			if (file_path == NULL)
			{
				free (path_copy);
				return (NULL);
			}
			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, command);

			if (stat(file_path, &buffer) == 0)
			{
				free(path_copy);
				return (file_path);
			}
			else
			{
				free(file_path);
				path_token = strtok(NULL, ":");
			}
		}
		free(path_copy);
	}
	if (stat(command, &buffer) == 0)
		return (_strdup(command));
	return (NULL);
}