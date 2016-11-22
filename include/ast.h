/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 14:27:27 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/22 23:02:59 by FannyHuang       ###   ########.fr       */
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

enum			e_type
{
	COMMAND, AND_OR, REDIRECTION, PIPE, HEREDOC
};

typedef struct	s_cmdwr
{
	char		*commands;
}				t_cmdwr;

union	u_left_right
{
	struct s_ast	*tree;
	t_cmdwr			*command;
};

typedef struct	s_operator
{
	char		*operator;
	uint8_t		len;
}				t_operator;

typedef struct	s_ast
{
	int				operator;
	char			*str;
	union u_left_right	left;
	union u_left_right	right;
	// struct s_ast	*left;
	// struct s_ast	*right;
}				t_ast;

// union	u_left_right
// {
// 	struct s_ast	*tree;
// 	t_cmdwr			*command;
// };

static const t_operator	g_operators[] = {
	{"||", 2}, //0
	{"&&", 2},//1
	{"<<", 2}, //2
	{">>", 2},//3
	{">", 1},//4
	{"<", 1},//5
	{"|", 1},//6
	{NULL, 0},
};

int				ast_create_elem(t_ast **lst, int operator, char *str);
size_t			ast_check_redirections(int operator, char *ptr, size_t *i);
int				ast_list_to_tree(t_ast **lst_tokens);
t_ast			*ast_search_for_operator(t_ast *lst_tokens, int what, _Bool right);

t_ast			*create_node(char *str);
void			insert_node(t_ast **root, int operator, char *str, int left);

t_ast			*create_tokens(char *line);

#endif
