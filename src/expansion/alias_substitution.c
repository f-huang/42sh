/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_substitution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 15:47:41 by fhuang            #+#    #+#             */
/*   Updated: 2016/12/20 17:31:04 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "libft.h"
#include "tools.h"
#include "ft_42sh.h"

static char	*is_alias(t_variable *lst_alias, char *word)
{
	t_variable	*ptr;
	char		*key;

	if (!word)
		return (ERROR);
	ptr = lst_alias;
	while (ptr)
	{
		if ((key = var_getkey(ptr->variable)))
		{
			if (ft_strequ(key, word))
			{
				ft_strdel(&key);
				return (ptr->variable);
			}
			ft_strdel(&key);
		}
		ptr = ptr->next;
	}
	return (NULL);
}

static int	switch_string(char **line, int i, char *plus, char *minus)
{
	char	*tmp;

	if (!plus || !minus)
		return (ERROR);
	if (!(tmp = ft_memalloc(ft_strlen(*line) + ft_strlen(plus) -\
		ft_strlen(minus) + 1)))
		return (ERROR);
	tmp = ft_strncat(tmp, *line, i);
	tmp = ft_strcat(tmp, plus);
	tmp = ft_strcat(tmp, *line + i + ft_strlen(minus));
	ft_strdel(&(*line));
	*line = tmp;
	return (GOOD);
}

static int	search_for_alias(t_variable *lst_alias, char **line,\
												char *initial_word, int *i)
{
	char	*value;
	char	*tmp_key;

	tmp_key = initial_word;
	while ((value = is_alias(lst_alias, tmp_key)))
	{
		value += ft_strlen(tmp_key) + 1;
		if (ft_strequ(initial_word, value))
			return (ERROR);
		else if (ft_strequ(tmp_key, value))
		{
			switch_string(line, *i, value, initial_word);
			*i = *i + ft_strlen(value);
			return (GOOD);
		}
		tmp_key = value;
	}
	if (!ft_strequ(initial_word, tmp_key))
	{
		switch_string(line, *i, tmp_key, initial_word);
		*i = *i + ft_strlen(tmp_key);
		return (GOOD);
	}
	return (ERROR);
}

static int	find_first_word(t_variable *lst_alias, char **line,\
													int *i, int first_word)
{
	int		end;
	char	*word;

	while ((*line)[*i] && tl_iswhitespace((*line)[*i]))
		++(*i);
	while ((*line)[*i] && (*line)[*i] != ';')
	{
		end = *i;
		while ((*line)[end] && !tl_iswhitespace((*line)[end])\
			&& (*line)[end] != ';')
			end++;
		if (first_word)
		{
			word = tl_strndup(*line + *i, (end - *i));
			search_for_alias(lst_alias, line, word, i);
			ft_strdel(&word);
		}
		first_word = 0;
		(*i)++;
	}
	return (GOOD);
}

int			alias_substitution(t_variable *lst_alias, char **line)
{
	int		i;
	int		len;

	if (!lst_alias)
		return (GOOD);
	len = ft_strlen(*line);
	i = 0;
	while (i < len)
	{
		find_first_word(lst_alias, line, &i, 1);
		while ((*line)[i] == ';')
			i++;
	}
	return (GOOD);
}
