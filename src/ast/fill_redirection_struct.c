/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_redirection_struct.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 18:32:18 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/24 10:24:26 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"
#include "tools.h"
#include "ft_42sh.h"

#define IS_REDIRECTION(x) (x >= 3 && x <= 5)

# define CLOSE_REDIRECT			(1 << 0)
# define SIMPLE_RIGHT_REDIRECT	(1 << 1)
# define SIMPLE_LEFT_REDIRECT	(1 << 2)
# define DOUBLE_RIGHT_REDIRECT	(1 << 3)
# define DOUBLE_LEFT_REDIRECT	(1 << 4)
# define FILE_REDIRECT			(1 << 5)

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

static t_redirections	*init_redir_struct(int operator)
{
	t_redirections	*new;

	if (!(new = (t_redirections*)ft_memalloc(sizeof(t_redirections))))
		return (ERROR);
	new->from_fd = -1;
	new->to_fd = -1;
	if (operator == 5)
		new->type |= SIMPLE_LEFT_REDIRECT;
	else if (operator == 4)
		new->type |= SIMPLE_RIGHT_REDIRECT;
	else if (operator == 3)
		new->type |= DOUBLE_RIGHT_REDIRECT;
	return (new);
}

static int		isworddigit(char *str)
{
	int		i;

	i = 0;
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

static void		debug_print_redir(t_redirections *new)
{
	ft_putendl("~~~~~~~~~~~~~~~~~~~~~~");
	if (new->type & SIMPLE_LEFT_REDIRECT)
		ft_putendlcol("<", MAGENTA);
	else if (new->type & SIMPLE_RIGHT_REDIRECT)
		ft_putendlcol(">", MAGENTA);
	else if (new->type & DOUBLE_RIGHT_REDIRECT)
		ft_putendlcol(">>", MAGENTA);
	ft_putstr("From fd : ");
	ft_putnbrendl(new->from_fd);
	ft_putstr("To fd : ");
	ft_putnbrendl(new->to_fd);
	if (new->type & CLOSE_REDIRECT)
		ft_putendlcol("Close -", YELLOW);
	else if (new->type & FILE_REDIRECT)
		ft_putstr("Dest File : ");
	if (new->dest)
		ft_putendlcol(new->dest, YELLOW);
	ft_putendl("~~~~~~~~~~~~~~~~~~~~~~");
}

static int		parse_redir_str(t_redirections **redir, t_ast *ptr, _Bool *file_redirect)
{
	t_redirections	*new;
	int				i;

	if (!(new = init_redir_struct(ptr->operator)))
		return (ERROR);
	i = 0;
	if (ft_isdigit(ptr->str[i]))
		new->from_fd = ft_atoi(ptr->str + i++);
	if (ft_strnequ(ptr->str + i, g_operators[ptr->operator].operator, g_operators[ptr->operator].len))
		i += g_operators[ptr->operator].len;
	if (ptr->str[i] == '&')
	{
		if (ptr->str[++i] == '-' && (tl_iswhitespace(ptr->str[i + 1]) || !ptr->str[i + 1]))
			new->type |= CLOSE_REDIRECT;
		else if (isworddigit(ptr->str + i))
			new->to_fd = ft_atoi(ptr->str + i);
	}
	if (new->to_fd == -1 && !(new->type & CLOSE_REDIRECT))
	{
		new->dest = ft_strtrim(ptr->str + i);
		new->type |= FILE_REDIRECT;
		*file_redirect = true;
	}
	debug_print_redir(new);
	return (redirection_push_back(redir, new));
}

t_redirections	*fill_redirection_struct(t_ast **list, t_ast *ptr, _Bool *file_redirect)
{
	t_redirections	*redir;

	redir = NULL;
	while (ptr && IS_REDIRECTION(ptr->operator))
	{
		if (!parse_redir_str(&redir, ptr, file_redirect))
			return (NULL);
		ast_remove_link(list, ptr);
		ptr = ptr->right;
	}
	return (redir);
}
