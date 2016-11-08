#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

typedef struct			s_environment
{
	char					env_variable;
	int						length;
	struct s_environment	*next;
}						t_environment;


#endif
