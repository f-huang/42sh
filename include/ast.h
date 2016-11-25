/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 14:27:27 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/25 19:36:21 by fhuang           ###   ########.fr       */
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

#ifndef IS_REDIRECTION
# define IS_REDIRECTION(x) (x >= 3 && x <= 5)
#endif

# define CLOSE_REDIRECT			(1 << 0)
# define SIMPLE_RIGHT_REDIRECT	(1 << 1)
# define SIMPLE_LEFT_REDIRECT	(1 << 2)
# define DOUBLE_RIGHT_REDIRECT	(1 << 3)
# define DOUBLE_LEFT_REDIRECT	(1 << 4)
# define FILE_REDIRECT			(1 << 5)

enum			e_type
{
	COMMAND = -1, AND, OR, PIPE, REDIRECTION, HEREDOC
};
/******************************************/
typedef	struct	s_redirections
{
	int						from_fd;
	int						to_fd;
	char					*dest;
	int						type;
	struct s_redirections	*next;
}				t_redirections;

typedef struct	s_cmdwr
{
	char			**command;
	t_redirections	*redir;
}				t_cmdwr;

/******************************************/

typedef struct	s_ast
{
	int				operator;
	char			*str;
	struct s_ast	*left;
	struct s_ast	*right;
	t_cmdwr			*cmd1;
	t_cmdwr			*cmd2;
}				t_ast;


t_ast			*ast_create_tree(char *line);
int				ast_create_elem(t_ast **lst, int operator, char *str);
void			ast_insert_elem_in_tree(t_ast **root, t_ast *new);
int				ast_parse_tree(t_ast *tree);
void			ast_remove_link(t_ast **lst, t_ast *link);
void			ast_destroy_tree(t_ast *tree);

// t_ast		*ast_to_cmdwr(t_ast *list);
int				ast_to_cmdwr(t_ast **list);

int				cmdwr_fill_struct(t_cmdwr **cmd, char *str);
size_t			cmdwr_check_redirections(char *str, int *i, int redirection);
int				redirection_create_elem(t_redirections **redir, char *str);

#endif
