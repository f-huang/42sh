# ===== Editable =====
NAME	:=	42sh
# ====================

# ===== Standard =====
OS		:=	$(shell uname)
CC		:=	clang -pipe
CFLAGS	:=	-Wall -Wextra -Werror -g3
SRCDIR	:=	src/
OBJDIR	:=	obj/
BINDIR	:=	bin/
INCDIR	:=	include/
LIBDIR	:=	libft/
INPDIR	:=	input/
DIRBUILTINS	:= obj/builtins/
SRC		:= $(shell find src -type d \( -path src/builtins/env -o -path src/builtins/echo \) -prune -o -type f -print)
OBJ		:= $(SRC:src/%.c=obj/%.o)
INC		:=	-I./$(INCDIR) -I./$(LIBDIR)$(INCDIR) -I./$(SRCDIR)$(INPDIR)
ifeq ($(OS),Linux)
LIB		:=	-lncurses
else
LIB		:=	-ltermcap
endif
LIBPATH	:=	-L./$(LIBDIR) -lft
CACHEF	:=	.cache_exists
HISTORY	:=	~/.42sh_history
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

.PHONY: all libft echo env norme clean fclean re
.SILENT:

all: $(NAME)
	echo "alias l='ls -lG'\\n" > ~/.42shrc

$(NAME): libft env echo $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LIBPATH) $(LIB) $(INC)
	printf $(BLUE)" $@ compiled!\n"$(EOC)

$(OBJDIR)%.o: $(SRCDIR)%.c $(CACHEF)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)
	printf $(BLUE)"|"$(EOC)

$(CACHEF):
	test -d $(OBJDIR) || mkdir $(OBJDIR)
	test -d $(DIRBUILTINS) || mkdir $(DIRBUILTINS)
	test -d $(DIRBUILTINS)alias || mkdir $(DIRBUILTINS)alias
	test -d $(DIRBUILTINS)unalias || mkdir $(DIRBUILTINS)unalias
	test -d $(DIRBUILTINS)cd || mkdir $(DIRBUILTINS)cd
	test -d $(DIRBUILTINS)read || mkdir $(DIRBUILTINS)read
	test -d $(DIRBUILTINS)setenv || mkdir $(DIRBUILTINS)setenv
	test -d $(DIRBUILTINS)unsetenv || mkdir $(DIRBUILTINS)unsetenv
	test -d $(DIRBUILTINS)exit || mkdir $(DIRBUILTINS)exit
	test -d $(DIRBUILTINS)export || mkdir $(DIRBUILTINS)export
	test -d $(DIRBUILTINS)unset || mkdir $(DIRBUILTINS)unset
	test -d $(OBJDIRENV) || mkdir $(OBJDIRENV)
	test -d $(OBJDIRECHO) || mkdir $(OBJDIRECHO)
	test -d $(OBJDIR)environment || mkdir $(OBJDIR)environment
	test -d $(OBJDIR)expansion || mkdir $(OBJDIR)expansion
	test -d $(OBJDIR)ast || mkdir $(OBJDIR)ast
	test -d $(OBJDIR)tools || mkdir $(OBJDIR)tools
	test -d $(OBJDIR)execution || mkdir $(OBJDIR)execution
	test -d $(OBJDIR)history || mkdir $(OBJDIR)history
	test -d $(OBJDIR)input || mkdir $(OBJDIR)input
	test -d $(BINDIR) || mkdir $(BINDIR)
	test -d $(CACHEF) || touch $(CACHEF)

%.c:
	printf $(RED)"Missing file : $@\n"$(EOC)

libft:
	make -C $(LIBDIR)

echo: $(OBJECHO)
	$(CC) $(CFLAGS) -o $(BINECHO) $(OBJECHO) $(LIBPATH) $(LIB) $(INC)
	printf $(BLUE)" $@ compiled!\n"$(EOC)

env: $(OBJENV)
	$(CC) $(CFLAGS) -o $(BINENV) $(OBJENV) $(LIBPATH) $(LIB) $(INC)
	printf $(BLUE)" $@ compiled!\n"$(EOC)

norme:
	norminette $(SRCDIR) $(INCDIR) | grep -v Norme -B1 || true
	norminette $(LIBFT)$(SRCDIR) $(LIBFT)$(INCDIR) | grep -v Norme -B1 || true

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
