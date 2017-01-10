#include "libft.h"

int			cd_error(int index, char *path)
{
	const char	*error_msg[] = {
		"Too many arguments.\n",
		"'HOME' variable not set.\n",
		"'OLDPWD' variable not set.\n",
		": No such file or directory.\n",
		": Not a directory.\n",
		": Permission denied.\n",
		NULL
	};

	ft_putstr_fd("cd : ", 2);
	if (index > 2 && index < 6 && path)
		ft_putstr_fd(path, 2);
	ft_putstr_fd(error_msg[index], 2);
	return (1);
}
