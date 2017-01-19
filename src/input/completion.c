/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <ataguiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 12:35:30 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/19 14:23:56 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "tools.h"

int			match(char *s1, char *s2)
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

static char	*two_step(char *s)
{
	if (ft_strchr(s, '/'))
		return (ft_strjoin(ft_strrchr(s, '/') + 1, "*"));
	else
		return (ft_strjoin(s, "*"));
}

void		completion(void)
{
	char	*pattern;
	char	**splitted;
	char	*needle;
	int		i;

	splitted = ft_strsplit_whitespace(*command());
	i = tl_arrlen(splitted);
	needle = i ? strdup_input(splitted[i - 1]) : strdup_input("");
	pattern = two_step(needle);
	if (ft_strchr(needle, '/'))
		linkcase(pattern, needle);
	else if (!splitted[1] && ft_getlast(*command()) != ' ')
		commandcase(pattern);
	else
		lastcase(pattern);
	tl_freedoubletab(splitted);
	splitted = NULL;
	ft_strdel(&needle);
	ft_strdel(&pattern);
}
