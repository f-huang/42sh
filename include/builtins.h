#ifndef BUILTINS_H
# define BUILTINS_H

#ifndef OLDPWD
# define OLDPWD 0
#endif

#ifndef NEWPWD
# define NEWPWD 1
#endif

#ifndef HOME
# define HOME 2
#endif

typedef	struct	s_bnb
{
	char		*builtin;
	int			(*function)(t_shell *, int, char **);
}				t_bnb;

int				builtin_cd(t_shell *sh, int ac, char **av);
int				builtin_setenv(t_shell *sh, int ac, char **av);
int				builtin_unsetenv(t_shell *sh, int ac, char **av);
int				builtin_exit(t_shell *sh, int ac, char **av);

#endif
