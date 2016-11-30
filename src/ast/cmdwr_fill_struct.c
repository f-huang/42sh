/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdwr_fill_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 13:27:36 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/30 03:01:52 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "ft_42sh.h"
#include "libft.h"
#include "tools.h"

static int
	is_operator(t_cmdwr **cmd, char *str, int *i, char *tmp, char **tab)
{
	static const char	*redir[] = {">>", "<<", ">", "<", NULL};
	int					j;
	int					len;

	j = -1;
	len = 0;
	while ((*i == 0 || str[*i - 1] != '\\') && redir[++j])
		if (ft_strnequ(redir[j], str + *i, ft_strlen(redir[j])))
		{
			len = cmdwr_check_redirections(str, i, j);
			if (tmp != NULL)
			{
				while (tl_iswhitespace(*tmp))
					tmp++;
				if (str + *i != tmp)
					*tab = tl_strndup(tmp, (size_t)(str + *i - tmp));
				redirection_create_elem(&(*cmd)->redirs,\
					tl_strndup(str + *i, ft_strlen(redir[j]) + len));
			}
			*i += len + 1;
			return (str + *i == tmp ? 2 : 1);
		}
	return (0);
}

static size_t	get_tablen(char *str)
{
	size_t	len;
	int		i;

	i = 0;
	len = str[i] ? 1 : 0;
	while (str[i] != 0)
	{
		if ((i == 0 || str[i - 1] != '\\') && (str[i] == '\'' || str[i] == '\"'))
			i += tl_jump_to_other_quote(str + i) + 1;
		else if (is_operator(NULL, str, &i, NULL, NULL))
			len--;
		else if (tl_iswhitespace(str[i]))
		{
			len++;
			while (tl_iswhitespace(str[i]))
				i++;
		}
		else
			i++;
	}
	return (len);
}

static int	is_word(char *str, int *i, char **tmp, char **tab)
{
	char	*ptr;

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

int		cmdwr_fill_struct(t_cmdwr **cmd, char *str)
{
	char	*tmp;
	int		i;
	int		j;
	int		ret;

	if (!((*cmd)->command = (char**)ft_memalloc(sizeof(char*) * (get_tablen(str) + 1))))
		return (ERROR);
	tmp = str;
	j = 0;
	i = 0;
	while (str[i])
	{
		if ((i == 0 || str[i - 1] != '\\') && (str[i] == '\'' || str[i] == '\"'))
			i += tl_jump_to_other_quote(str + i) + 1;
		else if ((ret = is_operator(cmd, str, &i, tmp, &(*((*cmd)->command + j)))))
		{
			j += ret - 1;
			while (tl_iswhitespace(str[i]))
				i++;
			tmp = str + i;
		}
		else if (is_word(str, &i, &tmp, &*((*cmd)->command + j)))
			j++;
		else
			i++;
	}
	if (!tl_isstrempty(tmp))
		(*cmd)->command[j++] = ft_strtrim(tmp);
	(*cmd)->command[j] = NULL;
	return (GOOD);
}
