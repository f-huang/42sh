/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sin_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 13:37:53 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/09 13:39:51 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

t_list	**ft_get_list(void)
{
	static t_list	*history = NULL;

	if (!history)
		history = ft_lstnew(NULL, 0);
	return (&history);
}

int		*ft_get_size(void)
{
	static int	size = 0;

	return (&size);
}

int		*ft_pos(void)
{
	static int	i = -1000;

	return (&i);
}
