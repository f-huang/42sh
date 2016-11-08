#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

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
	int						length;
	struct s_environment	*next;
}						t_environment;

int						create_link(t_environment **lst_env, char *variable);

char					*sh_getenv(t_environment *lst_env, char *key);
int						sh_setenv(t_environment **lst_env, char *key, char *value);

#endif
