/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 13:01:37 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/13 12:45:43 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	ft_init_input(void)
{
	cor()->x = 0;
	cor()->prompt_len = *prompt_len() + 1;
	*command() = strdup_input("");
}

int		input(void)
{
	int	key;

	key = 0;
	ft_init_input();
	while (1)
	{
		cor()->len = *command() ? ft_strlen(*command()) : 0;
		key = key_get();
		if (key == -3)
			continue ;
		(key != -2) ? key_dump(key) : 0;
		if (!key)
		{
			if (!(*dquote() % 2) && !(*quote() % 2))
			{
				reset_quotes();
				ft_putchar('\n');
				return (0);
			}
			else
			{
				if (*dquote() % 2)
					ft_putstr("dquote> ");
				else if (*quote() % 2)
					ft_putstr("quote> ");
			}
		}
		if (key == -1 && !(*command() && (*command())[0]) && !cor()->len)
			return (1);
	}
}
