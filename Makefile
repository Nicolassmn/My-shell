##
## EPITECH PROJECT, 2023
## header*
## File description:
## lolm
##

SRC		=	src/main.c												\
			src/design.c											\
			src/init_shell.c										\
			src/catch.c												\
			src/gestion_separators/architecture.c					\
			src/gestion_separators/pipe.c							\
			src/gestion_separators/sort_by_virgule.c				\
			src/gestion_separators/sort_with_double_pipe.c			\
			src/gestion_separators/first_sorting.c					\
			src/gestion_separators/second_sorting.c					\
			src/gestion_env/get_env.c								\
			src/gestion_env/setenv.c								\
			src/gestion_env/unsetenv.c								\
			src/gestion_env/copy_env.c								\
			src/gestion_cmd/bultin.c								\
			src/gestion_cmd/function_cd.c							\
			src/gestion_cmd/gestion_cmd.c							\
			src/gestion_cmd/too_long_path.c							\
			src/str_function/my_str_to_word_array.c					\
			src/str_function/my_putchar.c							\
			src/str_function/my_putstr.c							\
			src/str_function/my_atoi.c								\
			src/str_function/my_strcat.c							\
			src/str_function/my_strcmp.c							\
			src/str_function/my_strcpy.c							\
			src/str_function/my_strdup.c							\
			src/str_function/my_strlen.c							\
			src/str_function/nbr_to_str.c							\
			src/gestion_separators/thrid_sorting.c					\
			src/gestion_separators/redirection.c					\


OBJ		=	$(SRC:.c=.o)
NAME	=	mysh

CC		=	gcc
CFLAGS	=	-I ./include/ -Wextra -Wall -W -g

all:    	$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(OBJ) -o $@ $(CFLAGS)
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
			rm -f $(OBJ)

fclean: 	clean
			rm -f $(OBJ)
			rm -f $(NAME)

re:		fclean all

.PHONY:	all clean fclean re debug
