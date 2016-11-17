/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 03:33:41 by yfuks             #+#    #+#             */
/*   Updated: 2016/11/17 19:29:51 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include "execution.h"
#include "libft.h"

/*
**	TEST PURPOSE !
*/

static t_cmdwr	*get_exemple2(int print_info)
{
	t_cmdwr		*r;

	if (!(r = (t_cmdwr*)malloc(sizeof(t_cmdwr))))
		return (0);
	if (print_info)
	{
		ft_putendl("Creating command:");
		ft_putendl("cat <&- rien 1<&- <&1 rien2");
	}
	// cat <&- rien 1<&- <&1 rien2
	r->command = (char **)malloc(sizeof(char *) * 4);
	r->command[0] = ft_strdup("cat");
	r->command[1] = ft_strdup("rien");
	r->command[2] = ft_strdup("rien2");
	r->command[3] = 0;
	r->redirs = (t_redirections*)malloc(sizeof(t_redirections));

	// <&-
	r->redirs->type = CLOSE_REDIRECT | SIMPLE_LEFT_REDIRECT;
	r->redirs->from_fd = -1;
	r->redirs->to_fd = -1;
	r->redirs->dest = 0;

	// 1<&-
	r->redirs->next = (t_redirections*)malloc(sizeof(t_redirections));
	r->redirs->next->type = CLOSE_REDIRECT | SIMPLE_LEFT_REDIRECT;
	r->redirs->next->from_fd = 1;
	r->redirs->next->to_fd = -1;
	r->redirs->next->dest = 0;

	// <&1
	r->redirs->next->next = (t_redirections*)malloc(sizeof(t_redirections));
	r->redirs->next->next->type = SIMPLE_LEFT_REDIRECT;
	r->redirs->next->next->from_fd = -1;
	r->redirs->next->next->to_fd = 1;
	r->redirs->next->next->dest = 0;
	r->redirs->next->next->next = 0;
	return (r);
}

static t_cmdwr	*get_exemple1(int print_info)
{
	t_cmdwr		*r;

	if (!(r = (t_cmdwr*)malloc(sizeof(t_cmdwr))))
		return (0);
	if (print_info)
	{
		ft_putendl("Creating command:");
		ft_putendl("cat <&- rien 1<&- 2> error");
	}
	// cat <&- rien 1<&- 2> error
	r->command = (char **)malloc(sizeof(char *) * 3);
	r->command[0] = ft_strdup("cat");
	r->command[1] = ft_strdup("rien");
	r->command[2] = 0;
	r->redirs = (t_redirections*)malloc(sizeof(t_redirections));

	// <&-
	r->redirs->type = CLOSE_REDIRECT | SIMPLE_LEFT_REDIRECT;
	r->redirs->from_fd = -1;
	r->redirs->to_fd = -1;
	r->redirs->dest = 0;

	// 1<&-
	r->redirs->next = (t_redirections*)malloc(sizeof(t_redirections));
	r->redirs->next->type = CLOSE_REDIRECT | SIMPLE_LEFT_REDIRECT;
	r->redirs->next->from_fd = 1;
	r->redirs->next->to_fd = -1;
	r->redirs->next->dest = 0;

	// 2> error
	r->redirs->next->next = (t_redirections*)malloc(sizeof(t_redirections));
	r->redirs->next->next->type = SIMPLE_RIGHT_REDIRECT | FILE_REDIRECT;
	r->redirs->next->next->from_fd = 2;
	r->redirs->next->next->to_fd = -1;
	r->redirs->next->next->dest = ft_strdup("error");
	r->redirs->next->next->next = 0;
	return (r);
}

t_cmdwr		*get_redirection(char **command)
{
	t_cmdwr		*r;

	(void)command;
	r = get_exemple2(1);
	get_exemple1(0);
	return (r);
}
