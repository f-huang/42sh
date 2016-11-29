#ifndef HISTORY_H
# define HISTORY_H

# include "libft.h"

# ifndef HISTORY
#  define HISTORY "42sh_history" //need all path "~/.42sh_history"
# endif

int			init_history(t_list **all_history);
int			save_history(t_list *all_history);

#endif

