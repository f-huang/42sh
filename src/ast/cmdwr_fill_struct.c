/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdwr_fill_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 13:27:36 by fhuang            #+#    #+#             */
/*   Updated: 2016/12/01 16:38:12 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "ft_42sh.h"
#include "libft.h"
#include "tools.h"

static int		is_operator(t_cmdwr **cmd, char *str, char *tmp, t_index *index)
{
	static const char	*redir[] = {">>", "<<", ">", "<", NULL};
	int					j;
	int					len;

	j = -1;
	len = 0;
	while ((index->i == 0 || str[index->i - 1] != '\\') && redir[++j])
		if (ft_strnequ(redir[j], str + index->i, ft_strlen(redir[j])))
		{
			len = cmdwr_check_redirections(str, &index->i, j);
			if (tmp != NULL)
			{
				while (tl_iswhitespace(*tmp))
					tmp++;
				if (str + index->i != tmp)
					(*cmd)->command[index->j] =\
						tl_strndup(tmp, (size_t)(str + index->i - tmp));
				redirection_create_elem(&(*cmd)->redirs,\
					tl_strndup(str + index->i, ft_strlen(redir[j]) + len));
			}
			index->i += len + 1;
			return (str + index->i == tmp ? 2 : 1);
		}
	return (0);
}

static size_t	get_tablen(char *str)
{
	size_t				len;
	t_index				index;

	index.i = 0;
	len = str[index.i] ? 1 : 0;
	while (str[index.i] != 0)
	{
		if ((index.i == 0 || str[index.i - 1] != '\\') &&\
			(str[index.i] == '\'' || str[index.i] == '\"'))
			index.i += tl_jump_to_other_quote(str + index.i) + 1;
		else if (is_operator(NULL, str, NULL, &index))
			len--;
		else if (tl_iswhitespace(str[index.i]))
		{
			len++;
			while (tl_iswhitespace(str[index.i]))
				index.i++;
		}
		else
			index.i++;
	}
	return (len);
}

static int		is_word(char *str, int *i, char **tmp, char **tab)
{
	char				*ptr;

	if (!tl_iswhitespace(str[*i]))
		return (0);
	if (!(ptr = tl_strndup(*tmp, (size_t)(str + *i - *tmp))))
		return (-1);
	if (tl_isstrempty(ptr))
	{
		ft_strdel(&ptr);
		return (0);
	}
	*tab = ptr;
	while (str[*i] && tl_iswhitespace(str[*i]))
		(*i)++;
	*tmp = str + *i;
	return (1);
}

int				cmdwr_fill_struct(t_cmdwr **cmd, char *str)
{
	char				*tmp;
	t_index				index;
	int					ret;

	if (!((*cmd)->command = (char**)\
		ft_memalloc(sizeof(char*) * (get_tablen(str) + 1))))
		return (ERROR);
	tmp = str;
	ft_bzero(&index, sizeof(t_index));
	while (str[index.i])
	{
		if ((index.i == 0 || str[index.i - 1] != '\\') &&\
			(str[index.i] == '\'' || str[index.i] == '\"'))
			index.i += tl_jump_to_other_quote(str + index.i) + 1;
		else if ((ret = is_operator(cmd, str, tmp, &index)))
		{
			index.j += ret - 1;
			while (tl_iswhitespace(str[index.i]))
				index.i++;
			tmp = str + index.i;
		}
		else if (is_word(str, &index.i, &tmp, &*((*cmd)->command + index.j)))
			index.j++;
		else
			index.i++;
	}
	if (!tl_isstrempty(tmp))
		(*cmd)->command[index.j++] = ft_strtrim(tmp);
	(*cmd)->command[index.j] = NULL;
	return (GOOD);
}
