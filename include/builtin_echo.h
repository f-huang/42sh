#ifndef BUILTIN_ECHO_H
# define BUILTIN_ECHO_H

#ifndef NB_ESC_CHAR
# define NB_ESC_CHAR 9
#endif

typedef struct		s_escaped_char
{
	char		c;
	char		*escaped_char;
}					t_escaped_char;


int					check_for_options(bool option[2], char *str);
int					echo_strings(bool option[2], char *str);
#endif
