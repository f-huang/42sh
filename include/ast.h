/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 14:27:27 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/16 16:42:36 by fhuang           ###   ########.fr       */
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
	{"<<", 2},
	{">>", 2},
	{"||", 2},
	{"&&", 2},
	{">", 1},
	{"<", 1},
	{"|", 1},
	{NULL, 0},
};

t_ast			*create_node(char *str);
void			insert_node(t_ast **root, int operator, char *str, int left);

t_ast			*create_tokens(char *line);

#endif
