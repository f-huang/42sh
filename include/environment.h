/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 14:37:26 by fhuang            #+#    #+#             */
/*   Updated: 2016/12/08 14:37:27 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include <stdlib.h>

# ifndef DEFAULT_PATH
#  define DEFAULT_PATH "/bin:/usr/bin"
# endif

typedef struct			s_variable
{
	char				*variable;
	size_t				length;
	struct s_variable	*next;
}						t_variable;

int						create_elem(t_variable **lst_env, char *variable);
void					clear_env_list(t_variable **lst_env);

char					**lstenv_to_tab(t_variable *lst_env);

char					*sh_getenv(t_variable *lst_env, char *key);
int						sh_setenv(t_variable **lst_env, char *key, char *value);
int						sh_unsetenv(t_variable **lst_env, char *key);
void					sh_print_env(t_variable *lst_env);

#endif
