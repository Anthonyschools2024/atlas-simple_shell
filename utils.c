#include "shell.h"

/**
 * _strcmp - Compares two strings
 * @s1: First string
 * @s2: Second string
 *
 * Return: 0 if strings are equal, non-zero otherwise
 */

int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2)) /* While characters match continue comparing */
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2); /* Return matching word */
}