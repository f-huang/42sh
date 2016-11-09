#include "environment.h"
#include "libft.h"

void		sh_print_env(t_environment *lst_env)
{
	while (lst_env)
	{
		ft_putendl(lst_env->variable);
		lst_env = lst_env->next;
	}
}
