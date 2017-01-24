/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 14:47:57 by fhuang            #+#    #+#             */
/*   Updated: 2017/01/24 22:13:09 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/wait.h>
#include "ft_42sh.h"
#include "input.h"

#define PROMPT "$> "

extern	pid_t	g_id;

static void	reset_input(void)
{
	int	status;

	default_mode();
	code_end();
	ft_putchar('\n');
	if (waitpid(g_id, &status, 0) != -1)
	{
		if (g_id != -1)
			kill(g_id, SIGKILL);
	}
	else
		prompt();
	ft_strdel(command());
	*command() = ft_strdup("");
	ft_strdel(stock());
	*stock() = ft_strdup("");
	reset_quotes();
	raw_mode();
	cor()->len = 0;
	cor()->x = 0;
	clear_completion();
}

static void	sigquit_handler(void)
{
	int	status;

	if (waitpid(g_id, &status, 0) != -1)
	{
		if (g_id != -1)
			kill(g_id, SIGKILL);
		ft_putchar('\n');
	}
}

void		sig_handler(int signo)
{
	if (signo == SIGINT)
		reset_input();
	else if (signo == SIGQUIT)
		sigquit_handler();
	else if (signo == SIGTERM || signo == SIGKILL)
	{
		default_mode();
		exit(signo);
	}
}
