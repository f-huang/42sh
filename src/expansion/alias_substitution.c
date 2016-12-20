/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_substitution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 15:47:41 by fhuang            #+#    #+#             */
/*   Updated: 2016/12/20 16:41:56 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "libft.h"
#include "tools.h"
#include "ft_42sh.h"

static int	find_first_word(t_variable *lst_alias, char **line, int *i, int first_word)
{
	int	end;

	while ((*line)[*i] && tl_iswhitespace((*line)[*i]))
		++(*i);
	while ((*line)[*i] && (*line)[*i] != ';')
	{
		end = *i;
		while ((*line)[end] && !tl_iswhitespace((*line)[end]) && (*line)[end] != ';')
			end++;
		(void)lst_alias;
		// if (first_word)
			// search_for_alias(lst_alias, line, *i, end);
		first_word = 0;
		(*i)++;
	}
	return (GOOD);
}

int		alias_substitution(t_variable *lst_alias, char **line)
{
	int	i;

	if (!lst_alias)
		return (GOOD);
	i = 0;
	find_first_word(lst_alias, line, &i, 1);
	return (GOOD);
}
