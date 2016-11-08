# ===== Editable =====
NAME	:=	42sh
# ====================

# ===== Standard =====
CC		:=	clang
CFLAGS	:=	-Wall -Wextra -Werror -g3
SRCDIR	:=	src/
OBJDIR	:=	obj/
BINDIR	:=	bin/
INCDIR	:=	include/
LIBDIR	:=	libft/
SRC		:=	$(shell basename $(find $(SRCDIR) -type f \( -name '*.c' \)))
OBJ		:=	$(addprefix $(OBJDIR), $(SRC:.c=.o))
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

# ===== env =====
DIRENV	:=	src/env/
SRCENV	:=	$(shell ls $(DIRENV))
OBJENV	:=	$(addprefix $(OBJDIR), $(SRCENV:.c=.o))
# ===============

# ===== echo =====
DIRECHO	:=	src/echo/
SRCECHO	:=	$(shell ls $(DIRECHO))
OBJECHO	:=	$(addprefix $(OBJDIR), $(SRCECHO:.c=.o))
# ================

# ===== read =====
DIRREAD	:=	src/read/
SRCREAD	:=	$(shell ls $(DIRECHO))
OBJREAD	:=	$(addprefix $(OBJDIR), $(SRCREAD:.c=.o))
# ================

.PHONY: all libft echo env read norme clean fclean re
.SILENT:

all: $(NAME)

$(NAME): libft $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LIBPATH) $(LIB) $(INC)
	printf	$(BLUE)" $@ compiled!\n"$(EOC)

$(OBJDIR)%.o: $(SRCDIR)%.c $(CACHEF)
	$(CC) $(CFLAG) -c $< -o $@ $(INC)
	printf $(BLUE)"|"$(EOC)

$(CACHEF):
	test -d $(OBJDIR) || mkdir $(OBJDIR)
	test -d $(BINDIR) || mkdir $(BINDIR)
	test -d $(CACHEF) || touch $(CACHEF)

%.c:
	printf $(RED)"Missing file : $@\n"$(EOC)

libft:
	make -C $(LIBDIR)

echo: $(SRCECHO)%.c
	$(CC) $(CFLAGS) -c $< -o $(OBJDIR)%.o $(INC)

norme:
	printf $(RED)
	norminette $(SRCDIR) $(INCDIR) | grep -v Norme -B1 || true
	norminette $(LIBFT)src/ $(LIBFT)include/ | grep -v Norme -B1 || true
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
