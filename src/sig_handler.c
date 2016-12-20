/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 14:47:57 by fhuang            #+#    #+#             */
/*   Updated: 2016/12/20 19:42:25 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include <signal.h>

#define PROMPT "$> "

extern	t_shell	g_sh;

void		sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putchar('\n');
		prompt(&g_sh);
	}
}
