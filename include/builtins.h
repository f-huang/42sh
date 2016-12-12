/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 14:35:18 by fhuang            #+#    #+#             */
/*   Updated: 2016/12/12 19:13:21 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# ifndef OLDPWD
#  define OLDPWD 0
# endif

# ifndef NEWPWD
#  define NEWPWD 1
# endif

# ifndef HOME
#  define HOME 2
# endif

typedef	struct	s_bnb
{
	char		*builtin;
	int			(*function)(t_shell *, int, char **);
}				t_bnb;

int				builtin_setenv(t_shell *sh, int ac, char **av);
int				builtin_unsetenv(t_shell *sh, int ac, char **av);
int				builtin_exit(t_shell *sh, int ac, char **av);
int				builtin_export(t_shell *sh, int ac, char **av);
int				builtin_unset(t_shell *sh, int ac, char **av);

/*
**	CD
*/

int				builtin_cd(t_shell *sh, int ac, char **av);
_Bool			get_options(char **av, int *i);

/*
**	EXPORT
*/

void			print_export(t_shell *sh);

#endif
