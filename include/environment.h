#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include <stdlib.h>

#ifndef ERROR
# define ERROR 0
#endif

#ifndef GOOD
# define GOOD 1
#endif

#ifndef DEFAULT_PATH
# define DEFAULT_PATH "/bin:/usr/bin"
#endif

typedef struct			s_environment
{
	char					*variable;
	size_t					length;
	struct s_environment	*next;
}						t_environment;

int						create_elem(t_environment **lst_env, char *variable);
void					clear_env_list(t_environment **lst_env);

char					**lstenv_to_tab(t_environment *lst_env);

char					*sh_getenv(t_environment *lst_env, char *key);
int						sh_setenv(t_environment **lst_env, char *key, char *value);
int						sh_unsetenv(t_environment **lst_env, char *key);
void					sh_print_env(t_environment *lst_env);

#endif
