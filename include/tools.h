/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 18:12:33 by cjacquem          #+#    #+#             */
/*   Updated: 2016/11/10 17:25:06 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include <unistd.h>

char		*tl_str3join(char *s1, char *s2, char *s3);
char		*tl_strndup(const char *s1, size_t n);
char		*tl_strrealloc(char *s, size_t size);
int			*tl_strisalnum(char *s);
void		tl_freedoubletab(char **tab);

#endif
