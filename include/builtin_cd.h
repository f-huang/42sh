/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 18:02:35 by cjacquem          #+#    #+#             */
/*   Updated: 2016/11/09 18:02:37 by cjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_CD_H
# define BUILTIN_CD_H

#ifndef OLDPWD
# define OLDPWD 0
#endif

#ifndef NEWPWD
# define NEWPWD 1
#endif

#ifndef HOME
# define HOME 2
#endif

#include <unistd.h>
#include <limits.h>
#include "ft_42sh.h"
#include "builtin_cd.h"
#include "environment.h"
#include "libft.h"

int			builtin_cd(t_shell *sh, int ac, char **av);

#endif
