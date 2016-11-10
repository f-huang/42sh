/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tl_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 17:42:53 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/10 17:50:40 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tools.h"

int		tl_atoi_base(const char *str, int base)
{
	const char	*ptr;
	int			res;
	int			negatif;

	res = 0;
	ptr = str;
	while (*ptr && tl_isspace(*ptr))
		ptr++;
	negatif = *ptr == '-' ? -1 : 1;
	if (*ptr == '-' || *ptr == '+')
		ptr++;
	while (*ptr && ft_isdigit(*ptr))
	{
		res *= base;
		res += negatif * (*ptr - '0');
		ptr++;
	}
	return (res);
}
