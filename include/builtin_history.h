/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 14:28:23 by fhuang            #+#    #+#             */
/*   Updated: 2017/01/17 14:51:04 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_HISTORY_H
# define BUILTIN_HISTORY_H

# define OPTION_C		(1 << 0)
# define OPTION_D		(1 << 1)
# define OPTION_A		(1 << 2)
# define OPTION_N		(1 << 3)
# define OPTION_R		(1 << 4)
# define OPTION_W		(1 << 5)
# define OPTION_P		(1 << 6)
# define OPTION_S		(1 << 7)

/*
**	-c
**		Clear the history list. This can be combined with the other
**		options to replace the history list completely.
**
**	-d	offset
**		Delete the history entry at position offset.
**		offset should be specified as it appears when the history is displayed.
**
**	-a
**		Append the new history lines (history lines entered since
**		the beginning of the current Bash session) to the history file.
**
**	-n
**		Append the history lines not already read from the history file
**		to the current history list. These are lines appended to the
**		history file since the beginning of the current Bash session.
**
**	-r
**		Read the current history file and append its contents to the history list.
**
**	-w
**		Write out the current history to the history file.
**
**	-p
**		Perform history substitution on the args and display the result
**		on the standard output, without storing the results in the history list.
**
**	-s
**		The args are added to the end of the history list as a single entry.
*/

#endif
