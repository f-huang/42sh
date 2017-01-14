/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:23:46 by fhuang            #+#    #+#             */
/*   Updated: 2017/01/14 13:34:20 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include <dirent.h>
# include "ft_42sh.h"
# include "execution.h"

char					*substitute(t_shell *sh, char *cmd);
char					*dollar(t_shell *sh, char *acmd, char *ptr);
int						tilde(char **acmd);
char					*remove_quotes_and_backslash(char *cmd);

int						alias_substitution(t_variable *lst_alias, char **line);
#endif
