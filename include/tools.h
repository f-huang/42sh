/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <cjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 18:12:33 by cjacquem          #+#    #+#             */
/*   Updated: 2016/12/01 14:22:39 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

int			tl_isspace(int c);
int			tl_iswhitespace(int c);
int			tl_isstrempty(char *str);

int			*tl_strisalnum(char *s);

int			tl_atoi_base(const char *str, int base);

size_t		tl_jump_to_other_quote(char *ptr);

char		*tl_strrealloc(char *s, size_t size);
char		*tl_strndup(const char *s1, size_t n);
char		*tl_strmerge(char *origin, char *adding);
char		*tl_str3join(char *s1, char *s2, char *s3);

void		tl_freedoubletab(char **tab);
size_t		tl_arrlen(char **arr);

void		tl_lstaddend(t_list **alst, t_list *new_elem);
t_list		*tl_lstlast(t_list *lst);
t_list		*tl_lstnew(void *content, size_t size);
void		tl_del(void *data, size_t len);
void		tl_lstdelast(t_list **lst);

DIR			*tl_opendir(char *path);
int			*tl_closedir(DIR *dir);

#endif
