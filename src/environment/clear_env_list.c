/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_env_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 10:17:42 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/10 10:23:13 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "environment.h"
#include "libft.h"

void	clear_env_list(t_environment **lst_env)
{
	t_environment	*elem;
	t_environment	*ptr;

	elem = *lst_env;
	while (elem)
	{
		ptr = elem;
		elem = elem->next;
		ptr->length = 0;
		ft_strdel(&ptr->variable);
		ft_memdel((void*)&ptr);
	}
}
