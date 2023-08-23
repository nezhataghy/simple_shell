#include "main.h"

/**
 * execute - runs the command in a child process
 * @argv: command line
 * @arg: command
 */

void execute(char **argv, char *arg)
{
	__pid_t id;

	id = fork();
	if (!id)
	{

		if (execve(arg, argv, NULL) == -1 || access(arg, X_OK))
		{
			free_grid(argv);
			perror("./shell");
			exit(127);
		}
	}
	else
	{
		wait(NULL);
	}
}

