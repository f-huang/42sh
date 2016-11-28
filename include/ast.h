/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 17:14:15 by yfuks             #+#    #+#             */
/*   Updated: 2016/11/24 11:18:11 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "execution.h"
# include "ft_42sh.h"

#ifndef IS_REDIRECTION
# define IS_REDIRECTION(x) (x >= 3 && x <= 5)
#endif

enum			e_type
{
	COMMAND = -1, AND, OR, PIPE, HEREDOC
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

#endif
