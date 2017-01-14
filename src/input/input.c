/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 13:01:37 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/14 13:51:52 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	init_input(void)
{
	cor()->x = 0;
	cor()->prompt_len = *prompt_len() + 1;
	ft_strdel(command());
	*command() = strdup_input("");
}

int		input(void)
{
	int		key;

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
			if (!(*dquote() % 2) && !(*quote() % 2))
			{
				reset_quotes();
				!ft_strcmp(*stock(), *command()) || !(**stock()) ? ft_putchar('\n') : 0;
				ft_strdel(command());
				*command() = ft_strdup(*stock());
				ft_strdel(stock());
				return (0);
			}
			else
			{
				init_input();
				if (*dquote() % 2)
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
		}
		if (key == -1 && !(*command() && (*command())[0]) && !cor()->len)
			return (1);
	}
}
