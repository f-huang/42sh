/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_read.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:01:19 by fhuang            #+#    #+#             */
/*   Updated: 2016/12/09 17:05:25 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_READ_H
# define BUILTIN_READ_H

# define OPTION_D		(1 << 0)
# define OPTION_E		(1 << 1)
# define OPTION_N		(1 << 2)
# define OPTION_P		(1 << 3)
# define OPTION_R		(1 << 4)
# define OPTION_S		(1 << 5)
# define OPTION_T		(1 << 6)
# define OPTION_U		(1 << 7)

/*
**		-d : Delim = 1 char
**		-e : Write output in the terminal (Readline() ?)
**		-n : ?
**		-p : ?
**		-r : backslash(\) do not escape characters
**		-s : Dont echo input on terminal
**		-t : timeout
**		-u : read from given fd
*/

int				get_options(char **av, int *option);

#endif
