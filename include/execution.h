/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 16:09:11 by yfuks             #+#    #+#             */
/*   Updated: 2016/11/14 18:21:14 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# define ISDIRECTORY	125
# define CANNOTINVOKE	126
# define NOTFOUND		127

# include "environment.h"
# include "ft_42sh.h"

typedef struct	s_exec
{
	char		*command;
	int			builtin_not_binary;
}				t_exec;

int				exec_is_executable(char *filepath);
char			**exec_get_envpath(t_shell *sh);

int				exec_is_command(t_exec *ex, t_shell *sh, char **command, char **path);
int				exec_is_builtin(t_exec *ex, t_shell *sh, char **command);
int				exec_is_standalone(t_exec *ex, char **command, char **paths);
int				exec_is_file(char *filepath);
int				exec_is_directory(char *filepath);
int				exec_execute_command(t_exec *ex, t_shell *sh, char **command);

int				exec_print_command_error(int error, char *command_name);

#endif
