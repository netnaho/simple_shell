#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "simpleShell.h"

/**
 * interpret - reads the commands and stores as strings
 * @T: string read from input
 * Return: command in new memory space
 */
char **interpret(char *T)
{
	int c = 0, argdx = 0, str_no = 0;
	static char **cmdargs;/*for holding an array of strings as cmdargs[a][b]*/

	cmdargs = (char **) malloc(sizeof(char *) * (10));
	if (cmdargs == NULL)
	{
		perror("Malloc Error");
		exit(1);
	}
	do {
		if (T[c] != '\0' && T[c] != ' ' && T[c] != '\n' && T[c] != '\r')
		{
			if (argdx == 0) /*malloc at the start of string*/
			cmdargs[str_no] = (char *) malloc(sizeof(char) * 20);
			if (cmdargs[str_no] == NULL)
			{
				perror("Malloc Error");
				exit(1);
			}
			cmdargs[str_no][argdx] = T[c];/*copy character into string*/
			argdx++;
		}
		else if (T[c] == '\0' || T[c] == '\n' || T[c] == '\r' || T[c] == ' ')
		{
			if (argdx != 0)/*no string being processed*/
			{
				cmdargs[str_no][argdx] = '\0';
				argdx = 0;
				str_no++;
			}
			if (T[c] == '\0' || T[c] == '\n' || T[c] == '\r')
				break;
		}
		c++;
	} while (1);
	cmdargs[str_no] = 0; /*last string is NULL, required by execve*/
	return (cmdargs);
}
