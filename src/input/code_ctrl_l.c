#include "input.h"

extern	t_shell	g_sh;

void	code_ctrl_l(void)
{
	ft_putstr("\033[H\033[J");
	prompt(&g_sh);
	*command() && (*command())[0] ? ft_putstr(*command()) : 0;
}
