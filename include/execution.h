/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 16:09:11 by yfuks             #+#    #+#             */
/*   Updated: 2016/11/15 03:59:11 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# define ISDIRECTORY	125
# define CANNOTINVOKE	126
# define NOTFOUND		127

# include "environment.h"
# include "ft_42sh.h"

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

typedef struct	s_exec
{
	char		*command;
	int			builtin_not_binary;
}				t_exec;

typedef	struct	s_redirection
{
	char		*executable;
	char		**command;
	int			from_fd;
	int			to_fd;
	char		*dest;
	int			type;
}				t_redirection;

int				exec_is_executable(char *filepath);
char			**exec_get_envpath(t_shell *sh);

int				exec_is_command(t_exec *ex, t_shell *sh, char **command, char **path);
int				exec_is_builtin(t_exec *ex, t_shell *sh, char **command);
int				exec_is_standalone(t_exec *ex, char **command, char **paths);
int				exec_is_file(char *filepath);
int				exec_is_directory(char *filepath);
int				exec_execute_command(t_exec *ex, t_shell *sh, char **command);
int				exec_right_redirect(t_shell *sh, t_redirection *r);

int				exec_print_command_error(int error, char *command_name);

int				exec_redirection(t_shell *sh, t_redirection *r);
t_redirection	*get_redirection(char **command);
#endif
