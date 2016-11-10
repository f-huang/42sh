/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <cjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 18:12:33 by cjacquem          #+#    #+#             */
/*   Updated: 2016/11/10 17:53:23 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

int			tl_isspace(int c);
int			tl_atoi_base(const char *str, int base);
char		*tl_str3join(char *s1, char *s2, char *s3);
char		*tl_strndup(const char *s1, size_t n);
char		*tl_strrealloc(char *s, size_t size);
int			*tl_strisalnum(char *s);

#endif
