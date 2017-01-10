#ifndef FT_42SH_H
# define FT_42SH_H

/*
**	LIBRAIRIES
*/

# include <termios.h>
# include "libft.h"
# include "environment.h"
# include "history.h"

/*
**	STANDARD LIRAIRIES STRUCTURES
*/

typedef struct dirent	t_dirent;
/*
**	ino_t          d_ino;		* numéro d'inœud *
**	off_t          d_off;		* décalage jusqu'à la dirent suivante *
**	unsigned short d_reclen;	* longueur de cet enregistrement *
**	unsigned char  d_type;		* type du fichier *
**	char           d_name[256];	* nom du fichier *
*/

typedef struct stat		t_stat;
/*
**	dev_t     st_dev;			* ID du périphérique contenant le fichier *
**	ino_t     st_ino;			* Numéro inœud *
**	mode_t    st_mode;			* Protection *
**	nlink_t   st_nlink;			* Nb liens matériels *
**	uid_t     st_uid;			* UID propriétaire *
**	gid_t     st_gid;			* GID propriétaire *
**	dev_t     st_rdev;			* ID périphérique (si fichier spécial) *
**	off_t     st_size;			* Taille totale en octets *
**	blksize_t st_blksize;		* Taille de bloc pour E/S *
**	blkcnt_t  st_blocks;		* Nombre de blocs alloués *
**	time_t    st_atime;			* Heure dernier accès *
**	time_t    st_mtime;			* Heure dernière modification *
**	time_t    st_ctime;			* Heure dernier changement état *
*/

typedef struct termios	t_termios;
/*
**	tcflag_t	c_iflag;		* modes d'entrée *
**	tcflag_t	c_oflag;		* modes de sortie *
**	tcflag_t	c_cflag;		* modes de contrôle *
**	tcflag_t	c_lflag;		* modes locaux *
**	cc_t		c_cc[NCCS];		* caractères de contrôle *
*/

typedef struct winsize	t_winsize;
/*
**	unsigned short	ws_row;
**	unsigned short	ws_col;
**	unsigned short	ws_xpixel;
**	unsigned short	ws_ypixel;
*/

/*
**	RETURN VALUES
*/
# ifndef ERROR
#  define ERROR 0
# endif

# ifndef GOOD
#  define GOOD 1
# endif

/*
**	SHELL STRUCTURE AND DEFINES
*/

typedef struct			s_shell
{
	int					last_return;
	t_variable			*lst_env;
	t_variable			*lst_localvar;
	t_variable			*lst_alias;
	char				*bin_path;
	t_termios			term;
	t_winsize			*window;
	t_history			*lst_history;
}						t_shell;

typedef struct			s_bitfield
{
	unsigned int		squote : 1;
	unsigned int		dquote : 1;
	unsigned int		bslash : 1;
}						t_bitfield;

# ifndef BUFF_SIZE
#  define BUFF_SIZE 256
# endif

/*
**	BUILTIN CODE
*/
# ifndef BUILTIN
#  define BUILTIN "cd exit read unsetenv setenv export unset alias unalias"
# endif

# ifndef NBBUILTIN
#  define NBBUILTIN 6
# endif

/*
**	SHELL BASIC FUNCTIONS
*/

int						import_shrc(t_shell *sh);
int						init_shell(t_shell *sh, char *av_0);
void					clear_shell(t_shell *sh);

int						prompt(t_shell *sh);
int						get_line(int fd, char **line);
void					sig_handler(int signo);
void					loop_through_commands(t_shell *sh,\
							t_list *lst_commands);

int						pipe_command(void);
int						get_heredocs(t_shell *sh, t_list **lst);
int						exec_command(t_shell *sh, char **command);
int						lexer_parser(char **command_line, t_list **lst);

/* === TEMPORARY PROTO ATAGUIRO === */

# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <stdlib.h>
# include <dirent.h>
# include <termios.h>

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ipc.h>
# include <sys/ioctl.h>

/* === tools === */

typedef	struct	s_infos2
{
	int		words;
	char	**new;
	char	*tmp;
	int		t;
	int		i;
}				t_infos2;

typedef struct	s_clean
{
	int		j;
	size_t	i;
	int		dq;
	int		q;
	char	*new;
}				t_clean;

char				*ft_newclean(char *str);
char				ft_getlast(char *str);
void				ft_remove_shit(char ***new);
void				ft_replace_with_shit(char **s);
int					get_next_line_stdin(int fd, char **line);
void				ft_lstpushback(t_list **blst, void const *content,
						size_t content_size);
int					ft_lstsize(t_list *lst);
char				**ft_strsplit_whitespace(char *s);
char				ft_getlast(char *str);
char				*ft_strdup_input(char *src);

/* === end tools === */

# define CODE_CTRL_D -1
# define CODE_RETURN 0
# define CODE_TAB 1
# define CODE_BACK 2
# define CODE_UP 10
# define CODE_DOWN 20
# define CODE_RIGHT 30
# define CODE_LEFT 40
# define CODE_HOME 107
# define CODE_END 2016
# define CODE_SHIFT_UP 41
# define CODE_SHIFT_DOWN 42
# define CODE_SHIFT_RIGHT 43
# define CODE_SHIFT_LEFT 44
# define CODE_CTRL_X 100
# define CODE_CTRL_U 200
# define CODE_CTRL_W 300

#include <stdio.h>

typedef struct  s_termsize
{
		size_t      col;
		size_t      row;
}               t_termsize;

typedef struct  s_coord
{
		size_t      x;
		size_t      y;
		size_t      xmax;
		size_t      ymax;
		size_t      prompt_len;
		size_t      len;
}               t_coord;

typedef struct	s_comp
{
	char			*path;
	int				t;
	struct dirent	*lu;
	int				check;
	DIR				*dir;
	char			**splitted_path;
}				t_comp;

void  ft_manage_command(char c);
void  ft_stremove(void);
void  ft_fill_space(int j);
void  ft_strinsert_input(char c);

void completion(void);
void code_up(int key);
void code_right(void);
void code_left(void);
void code_down(int key);
void code_ctrl_d(void);
void code_return(int *key);
void code_home(void);
void code_end(void);
void code_shift_up(void);
void code_shift_down(void);
void code_shift_right(void);
void code_shift_left(void);
void code_ctrl_x(void);
void code_ctrl_u(void);
void code_ctrl_w(void);

int     match(char *s1, char *s2);
void    ft_linkcase(char *pattern, char *to_open);
void    ft_commandcase(char *pattern);
void    ft_lastcase(char *pattern);

int *prompt_len(void);
int get_x31(char c);
int get_x1b(char c);
int get_basics(char c);
char **user(void);
char **get_home(void);
t_coord *cor(void);
char ***env(void);
char  **copied(void);
int     ft_isvalid(char c);
char    *ft_newclean(char *str);
char  **command(void);
int         *dquote(void);
int         *quote(void);
t_termsize *ft_termsize(void);
void    ft_remove_display(char *to_add);
t_list  **ft_get_list(void);
int     *ft_pos(void);
int     *ft_get_size(void);
char    *ft_get_elem(int command);
void    ft_history(char *buffer);
void 	  ft_init_list(void);
void    ft_fill_space(int j);
char  *ft_getenv(const char *need);
void    ft_manage_quotes(void);
void    ft_reset_quotes(void);
char	**old_command(void);

/*  === TAB FUNCTIONS === */

size_t  ft_tablen(char **tabl);
char    **ft_tabdup(char **tabl);
char    **ft_tabstr(char **tabl, char *str);
void    ft_tabdel(char ***tabl);
int     ft_tabreplace(char ***tabl, char *str, char *by);

/* INPUT */

int     ft_input(void);
void    ft_raw_mode(void);
void    ft_default_mode(void);

/* === KEYS === */

size_t  key_is_ctrl_d(char *buff);
size_t  key_is_tab(char *buff);
int     key_get(void);
void    key_dump(int key);

/* === COMMANDS === */

void    ft_manage_command(char c);
void    ft_stremove(void);
void    ft_move_left(int x);
void    ft_move_right(int x);
void    ft_move_down(int x);
void    ft_move_up(int x);

#endif
