/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 15:45:47 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/18 17:25:21 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static void	display_second_prompt(void)
{
	init_input();
	if (*bs())
	{
		cor()->prompt_len = 2;
		ft_putstr("\n> ");
	}
	else if (*dquote() % 2)
	{
		cor()->prompt_len = 8;
		ft_putstr("dquote> ");
	}
	else if (*quote() % 2)
	{
		cor()->prompt_len = 7;
		ft_putstr("quote> ");
	}
}

static int	manage_return(void)
{
	if (!(*dquote() % 2) && !(*quote() % 2) && !(*bs()))
	{
		reset_quotes();
		!ft_strcmp(*stock(), *command()) || !(**stock()) ? ft_putchar('\n') : 0;
		ft_strdel(command());
		*command() = ft_strdup(*stock());
		ft_strdel(stock());
		return (0);
	}
	else
		display_second_prompt();
	return (1);
}

int			input(void)
{
	int		key;
	int		ret;

	key = 0;
	init_input();
	while (1)
	{
		cor()->len = ft_strlen(*command());
		key = key_get();
		if (key == -3)
			continue ;
		(key != -2 && key != -42) ? key_dump(key) : 0;
		if (!key)
		{
			code_end();
			*stock() = tl_strmerge(*stock(), *command());
			manage_quotes();
			ret = manage_return();
			if (!ret)
				return (0);
		}
		if (key == -1 && !(*command() && (*command())[0]) && !cor()->len)
			return (1);
	}
}
