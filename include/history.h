/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 16:36:29 by cjacquem          #+#    #+#             */
/*   Updated: 2016/12/05 18:39:41 by cjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

#ifndef HISTORY
# define HISTORY ".42sh_history"
#endif

typedef struct			s_history
{
	char				*command_line;
	struct s_history	*next;
}						t_history;

int			init_history(t_history **lst_history, t_variable *lst_env);
int			save_command_line(t_history **lst_history, char *command_line);
void		clear_history_list(t_history **lst_history, t_variable *lst_env);

#endif
