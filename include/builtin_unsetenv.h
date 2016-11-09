/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:59:49 by cjacquem          #+#    #+#             */
/*   Updated: 2016/11/09 18:01:36 by cjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_UNSETENV_H
# define BUILTIN_UNSETENV_H

#include "ft_42sh.h"

int			builtin_unsetenv(t_shell *sh, int ac, char **av);

#endif
