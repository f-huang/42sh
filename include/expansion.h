/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:23:46 by fhuang            #+#    #+#             */
/*   Updated: 2017/01/14 13:09:36 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include <dirent.h>
# include "ft_42sh.h"
# include "execution.h"

typedef struct	s_jobs
{
	pid_t			pgid;
	struct termios	tmodes;
	int				sterm;
	int				interact;
}				t_jobs;

extern t_jobs	g_jobs;

char					*substitute(t_shell *sh, char *cmd);
char					*dollar(t_shell *sh, char *acmd, char *ptr);
int						tilde(char **acmd);
char					*remove_quotes_and_backslash(char *cmd);
void					jobs_init(void);

int						alias_substitution(t_variable *lst_alias, char **line);
#endif
