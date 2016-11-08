#include "builtin_env.h"
#include <sys/stat.h>

int		env_is_executable(char *filepath)
{
	struct	stat	buff;

	if (stat(filepath, &buff) == 0 && buff.st_mode & S_IXUSR)
		return (1);
	return (0);
}
