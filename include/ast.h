/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 17:14:15 by yfuks             #+#    #+#             */
/*   Updated: 2016/11/28 11:54:41 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

#include <stdlib.h>

#ifndef GOOD
# define GOOD 1
#endif

#ifndef ERROR
# define ERROR 0
#endif

# include "ft_42sh.h"
# include "execution.h"

enum			e_type
{
	COMMAND = -1, AND, OR, PIPE, REDIRECTION, HEREDOC
};

typedef struct	s_ast
{
	int				operator;
	char			*str;
	struct s_ast	*left;
	struct s_ast	*right;
	t_cmdwr			*cmd1;
	t_cmdwr			*cmd2;
}				t_ast;

int				exec_ast(t_shell *sh, t_ast *ast);

t_ast			*ast_create_tree(char *line);
int				ast_create_elem(t_ast **lst, int operator, char *str);
void			ast_insert_elem_in_tree(t_ast **root, t_ast *new);
int				ast_parse_tree(t_ast *tree);
void			ast_remove_link(t_ast **lst, t_ast *link);
void			ast_destroy_tree(t_ast *tree);

int				ast_to_cmdwr(t_ast **list);

int				cmdwr_fill_struct(t_cmdwr **cmd, char *str);
size_t			cmdwr_check_redirections(char *str, int *i, int redirection);
int				redirection_create_elem(t_redirections **redir, char *str);

#endif
