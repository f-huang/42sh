# ===== Editable =====
NAME	:=	42sh
# ====================

# ===== Standard =====
CC		:=	clang
CFLAGS	:=	-g3 -Wall -Wextra -Werror
SRCDIR	:=	src
OBJDIR	:=	obj/
BINDIR	:=	bin/
INCDIR	:=	include/
LIBDIR	:=	libft/
#TOOLSDIR  := tools/
SUBDIR	:=	$(shell find $(SRCDIR) -type d -not -name $(SRCDIR) -exec basename {} '\' \;)
SRC		:=	$(shell find $(SRCDIR) -type f)
OBJ		:=	$(subst $(SRCDIR),$(OBJDIR),$(SRC:.c=.o))
INC		:=	-I./$(INCDIR) -I./$(LIBDIR)$(INCDIR)
LIB		:=	-ltermcap
LIBPATH	:=	-L./$(LIBDIR) -lft
CACHEF	:=	.cache_exists
HISTORY	:=	.42sh_history
# ====================

# ====== Colors ======
CLEAR		= "\033[2K"
UP			= "\033[A"
EOC			= "\033[0;0m"
BLACK		= "\033[0;30m"
RED			= "\033[0;31m"
GREEN		= "\033[0;32m"
YELLOW		= "\033[0;33m"
BLUE		= "\033[0;34m"
PURPLE		= "\033[0;35m"
CYAN		= "\033[0;36m"
WHITE		= "\033[0;37m"
# ====================

.PHONY: all libft norme clean fclean re tools debug
.SILENT:

all: $(NAME)

$(NAME): libft $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBPATH) $(LIB) $(INC)
	printf	$(BLUE)" $@ compiled!\n"$(EOC)

$(OBJDIR)%.o: $(SRCDIR)%.c $(CACHEF)
	$(CC) $(FLAG) -c $< -o $@ $(INC)
	printf $(BLUE)"|"$(EOC)

$(CACHEF):
	test -d $(OBJDIR) || mkdir $(OBJDIR)
	$(foreach dir,$(SUBDIR),\
		$(shell mkdir -p $(OBJDIR)$(dir))\
	)
	test -d $(BINDIR) || mkdir $(BINDIR)
	test -d $(CACHEF) || touch $(CACHEF)

%.c:
	printf $(RED)"Missing file : $@\n"$(EOC)

libft:
	make -C $(LIBDIR)

norme:
	printf $(RED)
	norminette $(SRCDIR) $(INCDIR) | grep -v Norme -B1 || true
	printf $(EOC)

clean:
	make -C $(LIBDIR) clean
	rm -rf $(OBJDIR) $(CACHEF)
	printf $(YELLOW)"All objects removed\n"$(EOC)

fclean: clean
	make -C $(LIBDIR) fclean
	test -d $(HISTORY) | rm -f $(HISTORY)
	rm -f $(NAME)
	rm -rf $(BINDIR)
	printf $(RED)"$(NAME) removed\n"$(EOC)

re: fclean all
