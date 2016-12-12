/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 18:50:15 by fhuang            #+#    #+#             */
/*   Updated: 2016/12/12 20:02:49 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "environment.h"
#include "ft_42sh.h"
#include "tools.h"

static size_t	get_tabsize(t_variable *lst_env, t_variable *lst_localvar, size_t *indexsize)
{
	t_variable	*ptr;
	size_t		nb_index;

	nb_index = 0;
	ptr = lst_env;
	while (ptr)
	{
		if (*indexsize < ptr->length)
			*indexsize = ptr->length;
		ptr = ptr->next;
		++nb_index;
	}
	ptr = lst_localvar;
	while (ptr)
	{
		if (*indexsize < ptr->length)
			*indexsize = ptr->length;
		ptr = ptr->next;
		++nb_index;
	}
	return (nb_index);
}

static int	copy_lst_to_tab(t_variable *lst_env, t_variable *lst_localvar, char ***tab, size_t indexsize)
{
	t_variable	*ptr;
	int			i;

	i = 0;
	ptr = lst_env;
	while (ptr)
	{
		if (!((*tab)[i++] = ft_strndup(ptr->variable, indexsize)))
			return (ERROR);
		ptr = ptr->next;
	}
	ptr = lst_localvar;
	while (ptr)
	{
		if (!((*tab)[i++] = ft_strndup(ptr->variable, indexsize)))
			return (ERROR);
		ptr = ptr->next;
	}
	return (GOOD);
}

static void	print_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		ft_putendlcol(tab[i++], CYAN);
}

int		print_export(t_shell *sh)
{
	char	**tab;
	size_t	nb_index;
	size_t	indexsize;

	tab = NULL;
	indexsize = 0;
	if (!(nb_index = get_tabsize(sh->lst_env, sh->lst_localvar, &indexsize)))
		return (GOOD);
	if (!(tab = (char**)ft_memalloc(sizeof(char*) * (nb_index + 1))))
		return (ERROR);
	copy_lst_to_tab(sh->lst_env, sh->lst_localvar, &tab, indexsize);
	print_tab(tab);
	tl_freedoubletab(tab);
	return (GOOD);
}
