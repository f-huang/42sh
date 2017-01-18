/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <cjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 16:36:29 by cjacquem          #+#    #+#             */
/*   Updated: 2017/01/18 19:52:45 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# ifndef HISTORY
#  define HISTORY ".42sh_history"
# endif

t_list			**get_full_list(void);
t_list			**get_new_list(void);


void			init_history_list(void);
int				save_command_line(char *command_line);
void			clear_history_list();
int				save_history_in_file(t_list *lst_history);

#endif
