/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 12:42:00 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/08 12:42:41 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	ft_strinsert_input(char c)
{
	char	*new;
	char	*to_add;

	to_add = NULL;
	new = ft_strnew(ft_strlen(*command()) + 2);
	new = ft_strcpy(new, *command());
	to_add = ft_strdup_input(&new[cor()->x]);
	new[cor()->x] = c;
	new[cor()->x + 1] = 0;
	ft_default_mode();
	ft_putchar(c);
	ft_raw_mode();
	if (cor()->x != cor()->len)
	{
		ft_putstr(to_add);
		ft_move_left(ft_strlen(to_add));
	}
	ft_strdel(command());
	*command() = ft_strjoin(new, to_add);
	ft_strdel(&to_add);
	ft_strdel(&new);
}

void	ft_fill_space(int j)
{
	int	i;

	i = 0;
	while (i < j + 1)
	{
		ft_putchar(' ');
		i++;
	}
	ft_move_left(j + 1);
}

void	ft_stremove(void)
{
	char	*cleaner;
	char	*to_add;

	if (!(*command() && (*command())[0]))
		return ;
	if (cor()->x > 0)
	{
		to_add = ft_strdup_input(&(*command())[cor()->x]);
		(cor()->x)--;
		ft_move_left(1);
		ft_remove_display(to_add);
		(*command())[cor()->x] = 127;
		cleaner = *command();
		(*command()) = ft_strdup_input(*command());
		ft_strdel(&cleaner);
		ft_strdel(&to_add);
	}
}

void	ft_manage_command(char c)
{
	ft_strinsert_input(c);
	(cor()->x)++;
}
