/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_last_entry.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 20:13:38 by fhuang            #+#    #+#             */
/*   Updated: 2017/01/18 20:13:58 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin_history.h"
#include "history.h"

void	delete_last_entry(t_hist_option tools)
{
	t_list	*lst;
	int		len;

	lst = *get_full_list();
	len = ft_lstlen(lst);
	history_del_position_offset(&lst, tools, len);
}
