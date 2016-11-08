#include "builtin_env.h"
#include <sys/wait.h>
#include <stdlib.h>
#include "libft.h"

static	int		get_command_status_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	else if (WIFSTOPPED(status))
		return (WSTOPSIG(status));
	return (0);
}

int		env_execute_command(char **env, char **av, int index_of_executable)
{
	pid_t	id;
	int		status;
	int		tmp;
	char	*executable;

	if (!(executable = env_get_command_path(env, av[index_of_executable])))
	{
		env_put_error(av[index_of_executable], "No such file or directory");
		return (NOTFOUND);
	}
	if (!env_is_executable(executable))
	{
		env_put_error(executable, "Permission denied");		
		free(executable);
		return (CANNOTINVOKE);
	}
	id = fork();
	if (id > 0)
	{
		waitpid(0, &tmp, WUNTRACED | WCONTINUED);
		free(executable);
		return (get_command_status_code(tmp));
	}
	else if (id == 0)
	{
		execve(executable, &av[index_of_executable], env);
		exit(NOTFOUND);
	}
	return (0);
}
