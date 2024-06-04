SRCS_L =	libft/ft_atoi.c\
			libft/ft_bzero.c\
			libft/ft_calloc.c\
			libft/ft_isalnum.c\
			libft/ft_isalpha.c\
			libft/ft_isascii.c\
			libft/ft_isdigit.c\
			libft/ft_isprint.c\
			libft/ft_itoa.c\
			libft/ft_lstadd_back.c\
			libft/ft_lstadd_front.c\
			libft/ft_lstclear.c\
			libft/ft_lstdelone.c\
			libft/ft_lstiter.c\
			libft/ft_lstlast.c\
			libft/ft_lstmap.c\
			libft/ft_lstnew.c\
			libft/ft_lstsize.c\
			libft/ft_memccpy.c\
			libft/ft_memchr.c\
			libft/ft_memcmp.c\
			libft/ft_memcpy.c\
			libft/ft_memmove.c\
			libft/ft_memset.c\
			libft/ft_putchar_fd.c\
			libft/ft_putendl_fd.c\
			libft/ft_putnbr_fd.c\
			libft/ft_putstr_fd.c\
			libft/ft_split.c\
			libft/ft_strchr.c\
			libft/ft_strdup.c\
			libft/ft_striteri.c\
			libft/ft_strjoin.c\
			libft/ft_strlcat.c\
			libft/ft_strlcpy.c\
			libft/ft_strlen.c\
			libft/ft_strmapi.c\
			libft/ft_strncmp.c\
			libft/ft_strnstr.c\
			libft/ft_strrchr.c\
			libft/ft_strtrim.c\
			libft/ft_substr.c\
			libft/ft_tolower.c\
			libft/ft_toupper.c\
			libft/ft_tab_size.c\

CC = cc

LIBFT = ./libft/libft.a
HEADER_LIB = libft/libft.h

CFLAGS = -g -Wall -Wextra -Werror

# Normal
NAME = cub3d
FUNC = srcs/cub3d.c srcs/error.c srcs/exit.c srcs/game.c srcs/cub3d_utils.c srcs/get_next_line.c srcs/parsing.c srcs/parsing_map.c srcs/parsing_utils.c srcs/minimap.c srcs/move.c
OBJ = $(patsubst srcs/%.c, obj/%.o, $(FUNC))

# Bonus
NAME_BONUS = cub3d_bonus
FUNC_BONUS = src_bonus/cub3d.c
OBJS_BONUS = ${FUNC_BONUS:.c=.o}

# Mlx
MLX_PATH = ./mlx/
MLX_FLAGS = -lX11 -lXext
MLX_LIB = mlx/libmlx_Linux.a

HEADER =	cub3d.h
# Compil
all: 	${NAME}

$(OBJ): ${HEADER} $(HEADER_LIB)

${NAME}: $(LIBFT) ${OBJ}
	make -C $(MLX_PATH) --no-print-directory
	${CC} ${OBJ} $(LIBFT) $(MLX_LIB) $(CFLAGS) $(MLX_FLAGS) -o $(NAME)

bonus: 	${NAME_BONUS}

#Libft
$(LIBFT): $(HEADER_LIB) $(SRCS_L)
	@echo "\n==> Making LIBFT"
	make -C ./libft

${NAME_BONUS}: ${OBJS_BONUS}
	make -C $(MLX_PATH) --no-print-directory
	${CC} ${CFLAGS} ${OBJS_BONUS} -o ${NAME_BONUS} -L$(MLX_PATH) $(MLX_FLAGS)

obj/%.o: srcs/%.c
	@mkdir -p obj/
	$(CC) $(FLAGS) -c $< -o $@

clean:	
	rm -rf obj
	rm -f ${OBJS_BONUS}
	@make -C ./libft clean
	@make clean -C ${MLX_PATH} --no-print-directory

fclean:	clean
	rm -f ${NAME}
	rm -f ${NAME_BONUS}
	@make -C ./libft fclean
	@make clean -C ${MLX_PATH} --no-print-directory

re:	fclean all

.PHONY: all clean fclean re bonus
