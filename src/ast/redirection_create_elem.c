/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_create_elem.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 18:32:18 by fhuang            #+#    #+#             */
/*   Updated: 2016/12/02 17:11:22 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"
#include "tools.h"
#include "ft_42sh.h"

static int		redirection_push_back(t_redirections **redir, t_redirections *new)
{
	t_redirections		*ptr;

	if (*redir)
	{
		ptr = *redir;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
	else
		*redir = new;
	return (GOOD);
}

static void		get_redir_type(t_redirections **new, char *str)
{
	static const char	*redir[] = {"<<", ">>", ">", "<", NULL};
	int					i;
	int					j;

	i = -1;
	while (str[++i])
	{
		j = -1;
		while (redir[++j])
			if (ft_strnequ(redir[j], str + i, ft_strlen(redir[j])))
			{
				if (j == 3)
					(*new)->type |= SIMPLE_LEFT_REDIRECT;
				else if (j == 2)
					(*new)->type |= SIMPLE_RIGHT_REDIRECT;
				else if (j == 1)
					(*new)->type |= DOUBLE_RIGHT_REDIRECT;
				else if (j == 0)
					(*new)->type |= DOUBLE_LEFT_REDIRECT;
				return ;
			}
	}
}

static int		isworddigit(char *str)
{
	int		i;

	i = 0;
	ft_putendlcol(str, MAGENTA);
	while (str[i] && tl_iswhitespace(str[i]))
		i++;
	while (str[i] && !tl_iswhitespace(str[i]))
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (i);
}

static int
	parse_redir_str(t_redirections **redir, t_redirections **new, char *str)
{
	int				i;

	i = 0;
	if (ft_isdigit(str[i]))
		(*new)->from_fd = ft_atoi(str + i++);
	if ((*new)->type & DOUBLE_RIGHT_REDIRECT || (*new)->type & DOUBLE_LEFT_REDIRECT)
		i++;
	if (str[++i] == '&' || (*new)->type & DOUBLE_LEFT_REDIRECT)
	{
		if ((*new)->type & DOUBLE_LEFT_REDIRECT && str[i] == '-' && (i++))
			(*new)->type |= CLOSE_REDIRECT;
		else if (!((*new)->type & DOUBLE_LEFT_REDIRECT))
		{
			if (str[++i] == '-' && (tl_iswhitespace(str[i + 1]) || !str[i + 1]))
			{
				(*new)->type |= CLOSE_REDIRECT;
				++i;
			}
			else if (isworddigit(str + i))
				(*new)->to_fd = ft_atoi(str + i);
		}
	}
	if ((*new)->to_fd == -1 || ((*new)->type & DOUBLE_LEFT_REDIRECT))
	{
		if ((*new)->type & DOUBLE_LEFT_REDIRECT || (*new)->to_fd == -1)
			(*new)->dest = ft_strtrim(str + i);
		if (!((*new)->type & DOUBLE_LEFT_REDIRECT))
			(*new)->type |= FILE_REDIRECT;
	}
	return (redirection_push_back(redir, *new));
}

int		redirection_create_elem(t_redirections **redir, char *str)
{
	t_redirections	*new;

	new = NULL;
	if (!(new = (t_redirections*)ft_memalloc(sizeof(t_redirections))))
	{
		ft_strdel(&str);
		return (ERROR);
	}
	new->from_fd = -1;
	new->to_fd = -1;
	new->next = NULL;
	new->dest = NULL;
	get_redir_type(&new, str);
	if (!parse_redir_str(redir, &new, str))
	{
		ft_strdel(&str);
		return (ERROR);
	}
	ft_strdel(&str);
	return (GOOD);
}
