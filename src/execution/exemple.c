#include "ast.h"
#include "libft.h"
# define CLOSE_REDIRECT		(1 << 0)

/*
+**	">"
+*/
# define SIMPLE_RIGHT_REDIRECT	(1 << 1)
/*
+**	"<"
+*/
# define SIMPLE_LEFT_REDIRECT	(1 << 2)

/*
+**	">>"
+*/
# define DOUBLE_RIGHT_REDIRECT	(1 << 3)

/*
+**	"<<"
+*/
# define DOUBLE_LEFT_REDIRECT	(1 << 4)

/*
+**	"< file"
+**	"1< file"
+**	"2> file"
+*/
# define FILE_REDIRECT			(1 << 5)
# define CYAN "\x1b[36m"
# define YELLOW "\x1b[33m"
# define COLOR_RESET "\x1b[0m"
static void	debug_print_tree(t_ast *root, int color)
{
	if (!root)
		return ;
	ft_putstr(color == 1 ? YELLOW: CYAN);
	ft_putstr(root->str);
	ft_putendl(COLOR_RESET);
	debug_print_tree(root->left, 1);
	debug_print_tree(root->right, 0);
}

t_ast	*exemple(void)
{
	t_ast	*tree;

	/* root = && */
	if (!(tree = (t_ast*)ft_memalloc(sizeof(t_ast))))
		return (NULL);
	tree->operator = AND_OR;
	tree->str = ft_strdup("&&");

	/* 			&&
	 		  /
			||
	*/
	t_ast	*left1;
	if (!(left1 = (t_ast*)ft_memalloc(sizeof(t_ast))))
		return (NULL);
	left1->operator = AND_OR;
	left1->str = ft_strdup("||");

	/* 			&&
	 		  /		\
			||		 |
	*/
	t_ast	*right1;
	if (!(right1 = (t_ast*)ft_memalloc(sizeof(t_ast))))
		return (NULL);
	right1->operator = PIPE;
	right1->str = ft_strdup("|");

	/* 			&&
	 		  /		\
			||		 |
					  \
					  	wc -l
	*/
	t_cmdwr	right1_2;
	if (!(right1_2.command = (char**)ft_memalloc(sizeof(char*) * 3)))
		return (NULL);
	right1_2.command[0] = ft_strdup("wc");
	right1_2.command[1] = ft_strdup("-l");
	right1_2.redir = NULL;

	/* 			&&
	 		  /		\
			||		 |
					/  \
				  |		wc -l
	*/
	t_ast	*right1_1;
	if (!(right1_1 = (t_ast*)ft_memalloc(sizeof(t_ast))))
		return (NULL);
	right1_1->operator = PIPE;
	right1_1->str = ft_strdup("|");

	/* 			&&
	 		  /		\
			||		 |
					/  \
				  |		wc -l
				/
		echo "Crotte"
	*/
	t_cmdwr	right1_1_1;
	if (!(right1_1_1.command = (char**)ft_memalloc(sizeof(char*) * 3)))
		return (NULL);
	right1_1_1.command[0] = ft_strdup("echo");
	right1_1_1.command[1] = ft_strdup("crotte");
	right1_1_1.redir = NULL;

	/* 			&&
			  /		\
			||		 |
					/  \
				  |		wc -l
				/	\
	echo "Crotte"	grep t
	*/
	t_cmdwr	right1_1_2;
	if (!(right1_1_2.command = (char**)ft_memalloc(sizeof(char*) * 3)))
		return (NULL);
	right1_1_2.command[0] = ft_strdup("grep");
	right1_1_2.command[1] = ft_strdup("t");
	right1_1_2.redir = NULL;

	/* 			&&
			  /				\
			||				 |
		/					/  \
	echo		  		  |		wc -l
						/	\
			echo "Crotte"	grep t
	*/
	t_cmdwr	left1_1;
	if (!(left1_1.command = (char**)ft_memalloc(sizeof(char*) * 3)))
		return (NULL);
	left1_1.command[0] = ft_strdup("echo");
	left1_1.command[1] = ft_strdup("Hamburger");
	if (!(left1_1.redir = (t_redirections*)ft_memalloc(sizeof(t_redirections))))
		return (NULL);
	left1_1.redir->from_fd = 1;
	left1_1.redir->to_fd = 2;
	left1_1.redir->type = SIMPLE_LEFT_REDIRECT;


	/* 			&&
			  /				\
			||				 |
		/		\			/  \
	echo		echo	  |		wc -l
						/	\
			echo "Crotte"	grep t
	*/
	t_cmdwr	left1_2;
	if (!(left1_2.command = (char**)ft_memalloc(sizeof(char*) * 3)))
		return (NULL);
	left1_2.command[0] = ft_strdup("echo");
	left1_2.command[1] = ft_strdup("<< Pizzas");
	if (!(left1_2.redir = (t_redirections*)ft_memalloc(sizeof(t_redirections))))
		return (NULL);
	left1_2.redir->from_fd = 0;
	left1_2.redir->to_fd = -1;
	left1_2.redir->type = SIMPLE_LEFT_REDIRECT | CLOSE_REDIRECT;

	if (!(left1_2.redir->next = (t_redirections*)ft_memalloc(sizeof(t_redirections))))
		return (NULL);
	left1_2.redir->next->from_fd = 1;
	left1_2.redir->next->to_fd = -1;
	left1_2.redir->next->type = SIMPLE_RIGHT_REDIRECT | FILE_REDIRECT;
	left1_2.redir->next->dest = ft_strdup("test1");


	/*	Link ||	*/
	left1->cmd1 = left1_1;
	left1->cmd2 = left1_2;

	/*	Link deuxieme |	*/
	right1_1->cmd1 = right1_1_1;
	right1_1->cmd2 = right1_1_2;

	/*	Link premier |	*/
	right1->right = right1_1;
	right1->cmd2 = right1_2;

	/*	Link &&	*/
	tree->left = left1;
	tree->right = right1;

	debug_print_tree(tree, 1);
	return (tree);
}
