/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 12:44:25 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/08 12:44:40 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	ft_init_input(void)
{
	cor()->x = 0;
	cor()->y = 0;
	cor()->xmax = 0;
	cor()->ymax = 0;
	cor()->prompt_len = *prompt_len() + 1;
	*command() = ft_strdup_input("");
}

int		ft_input(void)
{
	int	key;

	key = 0;
	ft_init_input();
	while (1)
	{
		cor()->len = *command() ? ft_strlen(*command()) : 0;
		key = key_get();
		(key != -2) ? key_dump(key) : 0;
		if (!key)
		{
			if (!(*dquote() % 2) && !(*quote() % 2))
			{
				ft_reset_quotes();
				ft_putchar('\n');
				return (0);
			}
			else
				ft_putstr(*dquote() % 2 ? "dquote> " : "quote> ");
		}
		if (key == -1 && !(*command() && (*command())[0]))
			return (1);
	}
}
