#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "simpleShell.h"

/**
 * get_line - function for reading between lines
 * @String: String to check
 * @n: size
 * @fd: Integer
 *
 * Return: number of chars read
 */

size_t get_line(char **String, size_t *n, int fd)
{
	size_t read_count = 0;
	int reads;
	char read_char[2];

	fflush(stdin);
	while (read_count < *n)
	{
		reads = read(fd, read_char, 1);
		if (reads == -1)
		{
			read_count = -1;
			break;
		}
		else if (reads == 1) /*a byte has been read*/
		{
			if (read_char[0] != '\t')
			{

			String[0][read_count] = read_char[0];
			read_count++;
			String[0][read_count] = '\0';
			if (read_char[0] == '\n')
				break;
			}
		}
	}
	return (read_count);
}
