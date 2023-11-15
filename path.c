#include "shell.h"

/**
 * find_path - Find the full path of a command.
 * @cmd: The command to find.
 *
 * Return: The full path of the command if found, NULL otherwise.
 */

char *find_path(char *cmd)
{
	char *path_env = getenv("PATH");
	char *path_copy, *token, *full_path;
	struct stat st;

	if (path_env == NULL)
		return (NULL);

	path_copy = strdup(path_env);
	if (path_copy == NULL)
		return (NULL);
	
	token = strtok(path_copy, ":");
	
	while (token != NULL)
	{
		full_path = strcat(strcat(token, "/"), cmd);
		
		if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
