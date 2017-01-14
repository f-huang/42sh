/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 13:06:12 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/14 13:25:24 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "input.h"
#include "ft_42sh.h"

t_jobs	g_jobs;

void	jobs_init(void)
{
	g_jobs.sterm = STDIN_FILENO;
	g_jobs.interact = isatty(g_jobs.sterm);

	if (g_jobs.interact)
	{
		while (tcgetpgrp(g_jobs.sterm) != (g_jobs.pgid = getpgrp()))
			kill (- g_jobs.pgid, SIGTTIN);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
		signal(SIGCHLD, SIG_IGN);
		g_jobs.pgid = getpid();
		setpgid(g_jobs.pgid, g_jobs.pgid);
		tcsetpgrp(g_jobs.sterm, g_jobs.pgid);
		tcgetattr(g_jobs.sterm, &g_jobs.tmodes);
	}
}
