/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <cjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 18:12:33 by cjacquem          #+#    #+#             */
/*   Updated: 2016/11/24 12:52:35 by cjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include <unistd.h>
# include "libft.h"

int			tl_isspace(int c);
int			tl_atoi_base(const char *str, int base);
char		*tl_str3join(char *s1, char *s2, char *s3);
char		*tl_strndup(const char *s1, size_t n);
char		*tl_strrealloc(char *s, size_t size);
int			*tl_strisalnum(char *s);
void		tl_freedoubletab(char **tab);
void		tl_del(void *data, size_t len);
void		tl_lstaddend(t_list **alst, t_list *new_elem);
size_t		tl_arrlen(char **arr);
t_list		*tl_lstlast(t_list *lst);
char		*tl_strmerge(char *origin, char *adding);

#endif
