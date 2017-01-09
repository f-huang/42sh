/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 12:47:58 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/08 12:48:25 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char	*ft_getenv(const char *need)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (*env() && (*env())[i])
	{
		if ((tmp = ft_strstr((*env())[i], need)) &&
				!ft_strncmp((*env())[i], (char *)need, ft_strlen(need)))
			break ;
		i++;
	}
	if (!tmp)
		return (NULL);
	return (&tmp[ft_strlen(need) + 1] ? &tmp[ft_strlen(need) + 1] : NULL);
}

void	ft_raw_mode(void)
{
	struct termios	tattr;

	tcgetattr(STDIN_FILENO, &tattr);
	tattr.c_lflag &= ~(ECHO | ICANON);
	tattr.c_oflag &= ~(OPOST);
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSADRAIN, &tattr);
}

void	ft_default_mode(void)
{
	struct termios	tattr;

	tcgetattr(STDIN_FILENO, &tattr);
	tattr.c_lflag |= (ECHO | ICANON);
	tattr.c_oflag |= (OPOST);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &tattr);
}
