CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror
LIB				=	-lreadline

NAME			=	minishell

LIBFT_DIR		=	libft
LIBFT			=	libft.a

HEADER			=	src/minishell.h

SRC_DIR			=	src
SRC				=	add_command_and_args.c		\
					cd.c						\
					check_if_path_not_expand.c	\
					check_path_data.c			\
					check_repeated_redirect.c	\
					check_syntax_error.c		\
					choice_command.c			\
					clean_cmd.c					\
					echo.c						\
					env.c						\
					environment.c				\
					error.c						\
					exit.c						\
					export.c					\
					fill_list_cmd_struct.c		\
					heredoc.c					\
					list_cmd_struct.c			\
					made_redirect.c				\
					main.c						\
					new_minishell.c				\
					parse.c						\
					pipex.c						\
					pipex2.c					\
					pipex3.c					\
					pipex4.c					\
					pwd.c						\
					signal.c					\
					unset.c						\
					utils.c						\
					utils_redirect.c

OBJ_DIR			=	obj
OBJ				=	$(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

.PHONY:	all clean fclean re

all:	$(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -j $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean:	clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re:		fclean all

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -c -o $@

$(OBJ_DIR):
	mkdir -p $@

$(NAME):	$(OBJ) $(HEADER)
	gcc $< -I libft -lft $(LIB) -o minishell
