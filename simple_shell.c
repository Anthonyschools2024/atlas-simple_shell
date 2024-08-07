#include "shell.h"

/**
 * main - Entry point
 * @ac: Argument count
 * @argv: Argument vector
 *
 * Description: This function serves as the entry point of the program.
 * It reads commands from the user, parses them into tokens, and executes
 * the correspoding commands.
 * 
 * Return: Always 0
 */
int main(int ac, char **argv)
{
    char *prompt = "(Eshell) $ ";
    char *lineptr = NULL, *lineptr_copy = NULL;
    size_t n = 0;
    ssize_t nchars_read;
    const char *delim = " \n";
    int num_tokens = 0;
    char *token;
    int i, j, interactive;
    int is_space_only = 1;

    (void)ac;

    while (1)
    {
        interactive = isatty(STDIN_FILENO);
        if (interactive)
        {
            printf("%s", prompt);
        }

        nchars_read = getline(&lineptr, &n, stdin);
        if (nchars_read == -1)
        {
            free(lineptr);
            exit(EXIT_SUCCESS);
        }
        
        for (j = 0; j < nchars_read - 1; j++)
        {
            if (lineptr[j] != ' ' && lineptr[j] != '\t')
            {
                is_space_only = 0;
                break;
            }
        }

        if (is_space_only)
        {
            free(lineptr);
            exit(EXIT_SUCCESS);
        }

        lineptr_copy = malloc(sizeof(char) * (nchars_read + 1));
        if (lineptr_copy == NULL)
            break;

        strcpy(lineptr_copy, lineptr);

        num_tokens = 0;
        token = strtok(lineptr, delim);

        while (token != NULL)
        {
            num_tokens++;
            token = strtok(NULL, delim);
        }
        num_tokens++;

        argv = malloc(sizeof(char *) * num_tokens);

        token = strtok(lineptr_copy, delim);

        for(i = 0; token != NULL; i++)
        {
            argv[i] = malloc(sizeof(char) * (strlen(token) + 1));
            strcpy(argv[i], token);
            token = strtok(NULL, delim); 
        }
        argv[i] = NULL;

        execmd(argv);

        for (i = 0; i < num_tokens - 1; i++)
        {
            free(argv[i]);
        }
        free(argv);
        free(lineptr_copy);
    }
    
    free(lineptr);

    return (0);
}