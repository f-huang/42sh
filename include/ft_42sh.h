#ifndef FT_42SH_H
# define FT_42SH_H

/*
**	OUR OWN LIBRAIRIES
*/

# include "libft.h"
# include "environment.h"
# include "ft_termcaps.h"

/*
**	C STANDARD LIBRARIES
*/

//# include <curses.h>
//# include <dirent.h>
//# include <errno.h>
//# include <fcntl.h>
//# include <signal.h>
//# include <stdio.h>
//# include <stdlib.h>
//# include <string.h>
//# include <sys/ioctl.h>
//# include <sys/stat.h>
//# include <sys/syslimits.h>
//# include <sys/types.h>
//# include <sys/uio.h>
//# include <sys/wait.h>
//# include <term.h>
//# include <termios.h>
//# include <unistd.h>

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
#ifndef ERROR
# define ERROR 0
#endif

#ifndef GOOD
# define GOOD 1
#endif

/*
**	SHELL STRUCTURE AND DEFINES
*/

typedef struct			s_shell
{
	int					last_return;
	t_environment		*lst_env;
	char				*bin_path;
	t_termios			*term;
	t_winsize			*window;
}						t_shell;

/*
**	MACRO
*/
#ifndef PROMPT
# define PROMPT "$> "
#endif

#ifndef BUFF_SIZE
# define BUFF_SIZE 64
#endif

/*
**	BUILTIN CODE
*/
#ifndef BUILTIN
# define BUILTIN "cd exit unsetenv setenv"
#endif

#ifndef NBBUILTIN
# define NBBUILTIN 4
#endif

/*
**	SHELL BASIC FUNCTIONS
*/

int						init_shell(t_shell *sh, char *av_0);
void					clear_shell(t_shell *sh);

int						prompt(t_shell *sh);
int						get_line(char **line);
void					sig_handler(int signo);
int						exec_command(t_shell *sh, char **command);

#endif
