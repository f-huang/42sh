/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_substitution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpoac <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 15:26:19 by tpoac             #+#    #+#             */
/*   Updated: 2017/02/03 13:42:50 by tpoac            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void		subshell_substitution(char **command)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!command && !*command)
		return ;
	command[0] = &command[0][1];
	while (command[i + 1])
		i++;
	while (command[i][j + 1])
		j++;
	command[i][j] = '\0';
}
