/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:23:46 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/28 18:59:09 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBSTITUTION_H
# define SUBSTITUTION_H

# include <dirent.h>
# include "ft_42sh.h"
# include "execution.h"

int						substitute(t_shell *sh, t_cmdwr *cmd);
int						dollar(t_shell *sh, char **acmd);
int						tilde(t_shell *sh, char **acmd);
DIR						*open_dir(char *path);
int						close_dir(DIR *dir);

#endif
