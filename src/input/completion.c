/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 12:35:30 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/11 12:47:02 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int		match(char *s1, char *s2)
{
	if (*s1 == 0 && *s2 == 0)
		return (1);
	if (*s1 != 0 && *s2 == '*')
		return (match(s1, s2 + 1) || (match(s1 + 1, s2)));
	if (*s1 == 0 && *s2 == '*')
		return (match(s1, s2 + 1));
	if (*s2 == *s1)
		return (match(s1 + 1, s2 + 1));
	return (0);
}

char	*two_step(char *s)
{
	if (ft_strchr(s, '/'))
		return (ft_strjoin(ft_strrchr(s, '/') + 1, "*"));
	else
		return (ft_strjoin(s, "*"));
}

void	completion(void)
{
	char	*pattern;
	char	**splitted;
	char	*needle;
	int		i;

	splitted = ft_strsplit_whitespace(*command());
	i = ft_tablen(splitted);
	needle = i ? strdup_input(splitted[i - 1]) : strdup_input("");
	pattern = two_step(needle);
	if (ft_strchr(needle, '/'))
		linkcase(pattern, needle);
	else if (!splitted[1] && ft_getlast(*command()) != ' ')
		commandcase(pattern);
	else
		lastcase(pattern);
	ft_tabdel(&splitted);
	ft_strdel(&needle);
	ft_strdel(&pattern);
}
