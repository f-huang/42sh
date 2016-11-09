#ifndef BUILTIN_CD_H
# define BUILTIN_CD_H

#ifndef OLDPWD
# define OLDPWD 0
#endif

#ifndef NEWPWD
# define NEWPWD 1
#endif

#ifndef HOME
# define HOME 2
#endif

int			builtin_cd(t_shell *sh, int ac, char **av);

#endif
