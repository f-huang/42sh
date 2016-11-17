/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 14:27:27 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/17 16:00:20 by fhuang           ###   ########.fr       */
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

/*
**	ex:
**	echo coucou > test
**	echo coucou 1> test
**	echo coucou >& 2
*/
# define SIMPLE_REDIRECT	(1 << 0)

/*
**	ex:
**	echo coucou >&-
**	echo coucou >& -
*/
# define CLOSE_REDIRECT		(1 << 1)

/*
**	">"
*/
# define SIMPLE_RIGHT_REDIRECT	(1 << 2)

/*
**	"<"
*/
# define SIMPLE_LEFT_REDIRECT	(1 << 3)

/*
**	">>"
*/
# define DOUBLE_RIGHT_REDIRECT	(1 << 4)

/*
**	"<<"
*/
# define DOUBLE_LEFT_REDIRECT	(1 << 5)

/*
**	"< file"
**	"1<&- file"
**	"2> file"
*/
# define FILE_REDIRECT			(1 << 6)

typedef struct	s_redirections
{
	int						from_fd;
	int						to_fd;
	char					*dest;
	int						type;
	struct s_redirections	*next;
}				t_redirections;

typedef struct  s_cmdwr
{
	char			**command;
	t_redirections	*redirs;
}				t_cmdwr;

typedef struct s_operator
{
	char		*operator;
	uint8_t		len;
}				t_operator;

typedef struct	s_ast
{
	int				operator;
	char			*str;
	struct s_ast	*left;
	struct s_ast	*right;
}				t_ast;

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
int				ast_create_syntax_tree(t_ast **lst_tokens);

t_ast			*create_node(char *str);
void			insert_node(t_ast **root, int operator, char *str, int left);

t_ast			*create_tokens(char *line);

#endif
