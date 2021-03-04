FILES = minishell.c
FILES += ft_get_next_line.c
FILES += ft_signal.c ft_exit.c ft_exec.c ft_run.c ft_console.c ft_quote.c
FILES += ft_getline.c ft_envctrl.c ft_parser.c ft_string.c ft_ioctrl.c
FILES += ./builtins/ft_builtins.c ./builtins/ft_cd.c \
         ./builtins/ft_echo.c  ./builtins/ft_env.c \
		 ./builtins/ft_export.c  ./builtins/ft_pwd.c \
		 ./builtins/ft_unset.c ./builtins/ft_builtins_util.c 
OBJS = ${FILES:%.c=%.o}
NAME = minishell
COMPILER = gcc
CFLAGS = -Wall -Wextra -Werror
CLFLAGS = -lft
HEADERPATH = ./
LIBFTPATH = ./libs/libft

$(NAME): $(OBJS)
	make bonus -C ${LIBFTPATH}
	$(COMPILER) $(CFLAGS) $(OBJS) -I$(HEADERPATH) -I${LIBFTPATH} -L$(LIBFTPATH) $(CLFLAGS) -o $(NAME)

%.o: %.c
	$(COMPILER) ${CFLAGS} -I${HEADERPATH} -I${LIBFTPATH} -c -o $@ $<

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	make fclean -C ${LIBFTPATH}
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean