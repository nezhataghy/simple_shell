#include "main.h"

int main(void);

/**
 * main - Entry point
 * Return: 0 on success
 */

int main(void)
{
	char **argv = NULL;
	char *buffer = NULL, *pathname = NULL;
	size_t n = 1024;
	ssize_t num_read = 0;
	const char *separator = " \n\t\r";

	if (isatty(STDIN_FILENO))
	{
		while (1998)
		{
			write(1, "#cisfun$ ", 10);
			num_read = getline(&buffer, &n, stdin);
			if (num_read == -1)
			{
				free(buffer);
				buffer = NULL;
				return (-1);
			}

			if (_strcmp(buffer, "env\n") == 0)
				print_env();

			else if (_strcmp(buffer, "exit\n") == 0)
			{
				free(buffer);
				buffer = NULL;
				exit(0);
			}
			else
			{
				buffer[num_read - 1] = '\0';
				if (access(buffer, X_OK) == 0)
				{
					argv = parsing(buffer, separator);

					if (argv)
					{
						execute(argv, buffer);
					}
					else
					{
						free(buffer);
						buffer = NULL;
						exit(0);
					}
					free_grid(argv);
					argv = NULL;
				}
				else
				{
					argv = parsing(buffer, separator);

					if (argv)
					{
						pathname = search_pathname(argv[0]);
						execute(argv, pathname);
					}
					free(pathname);
					pathname = NULL;
					free_grid(argv);
				}
			}
			free(buffer);
			buffer = NULL;
		}
	}
	else
	{
		while ((num_read = getline(&buffer, &n, stdin)) != -1)
		{
			buffer[num_read - 1] = '\0';
			if (_strcmp(buffer, "env") == 0)
				print_env();
			else if (_strcmp(buffer, "exit") == 0)
			{
				free_ptr(buffer);
				exit(0);
			}
			else
			{
				argv = parsing(buffer, separator);

				if (argv)
				{
					pathname = search_pathname(argv[0]);

					if (access(pathname, X_OK) == 0)
					{
						execute(argv, pathname);
					}
					if (pathname != argv[0])
					{
						free_ptr(pathname);
					}
					free_grid(argv);
				}
			}
		}
		free_ptr(buffer);
	}
	return (0);
}

/**
 * free_grid - frees the 2D array
 * @argv: array of args
 */
void free_grid(char **argv)
{
	int i = 0;

	if (argv != NULL)
	{
		while (argv[i] != NULL)
		{
			free(argv[i]);
			i++;
		}
		free(argv);
	}
}

/**
 * free_ptr - frees safely the ptr
 * @ptr: pointer
 */
void free_ptr(char *ptr)
{
	free(ptr);
	ptr = NULL;
}

