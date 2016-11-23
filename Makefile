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
DIRBUILTINS	:= obj/builtins/
SRC		:= $(shell find src -type d \( -path src/builtins/env -o -path src/builtins/echo -o -path src/builtins/read \) -prune -o -type f -print)
OBJ		:= $(SRC:src/%.c=obj/%.o)
INC		:=	-I./$(INCDIR) -I./$(LIBDIR)$(INCDIR)
LIB		:=	-ltermcap
LIBPATH	:=	-L./$(LIBDIR) -lft -L./$(LIBDIR)lib -lftprintf
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
DIRENV	:=	src/builtins/env/
OBJDIRENV	:= obj/builtins/env/
BINENV	:= bin/env
SRCENV	:= $(shell find src/builtins/env -type f -print)
OBJENV	:= $(SRCENV:src/builtins/env/%.c=obj/builtins/env/%.o)
# ===============

# ===== echo =====
DIRECHO	:=	src/builtins/echo/
OBJDIRECHO	:= obj/builtins/echo/
BINECHO	:=	bin/echo
SRCECHO	:=	$(shell find src/builtins/echo -type f -print)
OBJECHO	:=	$(SRCECHO:src/builtins/echo/%.c=obj/builtins/echo/%.o)
# ================

# ===== read =====
DIRREAD	:=	src/builtins/read/
OBJDIRREAD	:= obj/builtins/read/
BINREAD	:=	bin/read
SRCREAD	:=	$(shell find src/builtins/read -type f -print)
OBJREAD	:=	$(SRCREAD:src/builtins/read/%.c=obj/builtins/read/%.o)
# ================

.PHONY: all libft echo env read norme clean fclean re
.SILENT:

all: $(NAME)

$(NAME): libft env echo read $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LIBPATH) $(LIB) $(INC)
	printf	$(BLUE)" $@ compiled!\n"$(EOC)

$(OBJDIR)%.o: $(SRCDIR)%.c $(CACHEF)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)
	printf $(BLUE)"|"$(EOC)

$(CACHEF):
	test -d $(OBJDIR) || mkdir $(OBJDIR)
	test -d $(DIRBUILTINS) || mkdir $(DIRBUILTINS)
	test -d $(DIRBUILTINS)cd || mkdir $(DIRBUILTINS)cd
	test -d $(DIRBUILTINS)setenv || mkdir $(DIRBUILTINS)setenv
	test -d $(DIRBUILTINS)unsetenv || mkdir $(DIRBUILTINS)unsetenv
	test -d $(DIRBUILTINS)exit || mkdir $(DIRBUILTINS)exit
	test -d $(OBJDIRENV) || mkdir $(OBJDIRENV)
	test -d $(OBJDIRECHO) || mkdir $(OBJDIRECHO)
	test -d $(OBJDIRREAD) || mkdir $(OBJDIRREAD)
	test -d $(OBJDIR)environment || mkdir $(OBJDIR)environment
	test -d $(OBJDIR)ast || mkdir $(OBJDIR)ast
	test -d $(OBJDIR)tools || mkdir $(OBJDIR)tools
	test -d $(OBJDIR)execution || mkdir $(OBJDIR)execution
	test -d $(OBJDIR)termcaps || mkdir $(OBJDIR)termcaps
	test -d $(BINDIR) || mkdir $(BINDIR)
	test -d $(CACHEF) || touch $(CACHEF)

%.c:
	printf $(RED)"Missing file : $@\n"$(EOC)

libft:
	make -C $(LIBDIR)

read: $(OBJREAD)
	$(CC) $(CFLAGS) -o $(BINREAD) $(OBJREAD) $(LIBPATH) $(LIB) $(INC)
	printf	$(BLUE)" $@ compiled!\n"$(EOC)

echo: $(OBJECHO)
	$(CC) $(CFLAGS) -o $(BINECHO) $(OBJECHO) $(LIBPATH) $(LIB) $(INC)
	printf	$(BLUE)" $@ compiled!\n"$(EOC)

env: $(OBJENV)
	$(CC) $(CFLAGS) -o $(BINENV) $(OBJENV) $(LIBPATH) $(LIB) $(INC)
	printf	$(BLUE)" $@ compiled!\n"$(EOC)

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
