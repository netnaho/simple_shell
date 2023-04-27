#include <signal.h>
#include <sys/wait.h>
#include "simpleShell.h"

/**
 * execute - executes commands
 * @cmds: string containing command
 * @pat: path of command
 * Return: nothing
 */
void execute(char **cmds, char **pat)
{
	int er;
	pid_t cld, wait_pid;/*child pid and pid returned by wait*/
	int exit_status;/*child exit status*/

	if (pat[0] == NULL)
		er = 0;
	if (cmds != NULL)/*command not blank*/
	{
		cld = fork(); /*create child*/
		if (cld == -1)
		{
			perror("Error creating child process");
			exit(1);
		}
		else if (cld == 0) /*is child process*/
		{
			er = execve(cmds[0], cmds, NULL);
			if (er == -1)
			{
				perror("./shell: 1");/*display error in text format*/
				exit(1);
			}
		}
		else /*parent process*/
		{
			wait_pid = wait(&exit_status); /*wait for child to finish*/
			if (wait_pid == cld)
			kill(cld, SIGTERM); /*kill the child*/
		}
	}
}
