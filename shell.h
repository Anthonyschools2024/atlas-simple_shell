#infdef SHELL_H
#define SHELL_H

#include &lt;stdlib.h&gt;
#include &lt;stdio.h&gt;
#include &lt;string.h&gt;
#include &lt;unisted.h&gt;

int main (void);
void tokenize_input(cahr *input, char **args);
void get_command(char **input);
int is_background(char *args);