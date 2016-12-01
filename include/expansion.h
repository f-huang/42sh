/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:23:46 by fhuang            #+#    #+#             */
/*   Updated: 2016/12/01 21:30:46 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include <dirent.h>
# include "ft_42sh.h"
# include "execution.h"

int						substitute(t_shell *sh, t_cmdwr *cmd);
char					*dollar(t_shell *sh, char *acmd, char *ptr);
int						tilde(t_shell *sh, char **acmd);

#endif
