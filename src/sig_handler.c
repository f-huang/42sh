/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 14:47:57 by fhuang            #+#    #+#             */
/*   Updated: 2017/01/11 22:17:05 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include <signal.h>

#define PROMPT "$> "

extern	t_shell	g_sh;
extern	pid_t	g_id;

void	reset_input(void)
{
	ft_default_mode();
	ft_putchar('\n');
	if (g_id == -1)
		prompt(&g_sh);
	else
	{
		if (kill(g_id, SIGKILL) == -1)
			prompt(&g_sh);
	}
	ft_strdel(command());
	*command() = ft_strdup("");
	ft_reset_quotes();
	ft_raw_mode();
	cor()->x = 0;
}

void		sig_handler(int signo)
{
	if (signo == SIGINT)
		reset_input();
}
