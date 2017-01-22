/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <cjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 18:12:33 by cjacquem          #+#    #+#             */
/*   Updated: 2017/01/21 15:52:42 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# ifndef GNL_STRUCT
#  define GNL_STRUCT

typedef struct	s_gnl
{
	int				fd;
	char			*lfo;
}				t_gnl;

# endif

# ifndef BUFF_SIZE
#  define BUFF_SIZE 1096
# endif

int				tl_isspace(int c);
int				tl_iswhitespace(int c);
int				tl_is_whitespace_in_str(char *str);
int				tl_isstrempty(char *str);
int				tl_isstrdigit(char *str);

int				*tl_strisalnum(char *s);

int				tl_atoi_base(const char *str, int base);

long long		tl_atoll(const char *str);

size_t			tl_jump_to_other_quote(char *ptr);

char			*tl_strrealloc(char *s, size_t size);
char			*tl_strndup(const char *s1, size_t n);
char			*tl_switch_string(char *line, int i, char *plus, char *minus);
// int				tl_switch_string(char **line, int i, char *plus, char *minus);
char			*tl_strmerge(char *origin, char *adding);
char			*tl_str3join(char *s1, char *s2, char *s3);

void			tl_freedoubletab(char **tab);
size_t			tl_arrlen(char **arr);

void			tl_lstaddend(t_list **alst, t_list *new_elem);
t_list			*tl_lstlast(t_list *lst);
t_list			*tl_lstnew(void *content, size_t size);
void			tl_del(void *data, size_t len);
void			tl_lstdelast(t_list **lst);
void			tl_lstfree(t_list **begin);

int				tl_get_next_line(int const fd, char **line);
DIR				*tl_opendir(char *path);
int				*tl_closedir(DIR *dir);

#endif
