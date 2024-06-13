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
NAME = cub3D
FUNC = srcs/cub3d.c srcs/error.c srcs/exit.c srcs/game.c srcs/cub3d_utils.c srcs/get_next_line.c srcs/parsing.c srcs/parsing_map.c srcs/parsing_utils.c \
		srcs/move.c srcs/raycasting.c srcs/draw_line.c
OBJ = $(patsubst srcs/%.c, obj/%.o, $(FUNC))

# Bonus
NAME_BONUS = cub3D_bonus
FUNC_BONUS =	srcs_bonus/cub3d.c\
				srcs_bonus/cub3d_utils.c\
				srcs_bonus/draw_line.c\
				srcs_bonus/error.c\
				srcs_bonus/exit.c\
				srcs_bonus/game.c\
				srcs_bonus/get_next_line.c\
				srcs_bonus/minimap.c\
				srcs_bonus/move.c\
				srcs_bonus/parsing.c\
				srcs_bonus/parsing_map.c\
				srcs_bonus/parsing_utils.c\
				srcs_bonus/raycasting.c\

OBJ_BONUS = $(patsubst srcs_bonus/%.c, obj_bonus/%.o, $(FUNC_BONUS))

# Mlx
MLX_PATH = ./mlx/
MLX_FLAGS = -lX11 -lXext -lm
MLX_LIB = mlx/libmlx_Linux.a

HEADER =	cub3d.h
HEADER_BONUS = cub3d_bonus.h
# Compil
all: 	${NAME}

$(OBJ): ${HEADER} $(HEADER_LIB)

$(OBJ_BONUS): ${HEADER_BONUS} $(HEADER_LIB)

${NAME}: $(LIBFT) ${OBJ}
	make -C $(MLX_PATH) --no-print-directory
	${CC} ${OBJ} $(LIBFT) $(MLX_LIB) $(CFLAGS) $(MLX_FLAGS) -o $(NAME)

bonus: 	${NAME_BONUS}

${NAME_BONUS}: $(LIBFT) ${OBJ_BONUS}
	make -C $(MLX_PATH) --no-print-directory
	${CC} ${OBJ_BONUS} $(LIBFT) $(MLX_LIB) $(CFLAGS) $(MLX_FLAGS) -o $(NAME_BONUS)

$(LIBFT): $(HEADER_LIB) $(SRCS_L)
	@echo "\n==> Making LIBFT"
	make -C ./libft

obj_bonus/%.o: srcs_bonus/%.c
	@mkdir -p obj_bonus/
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: srcs/%.c
	@mkdir -p obj/
	$(CC) $(CFLAGS) -c $< -o $@

clean:	
	rm -rf obj
	rm -rf obj_bonus
	@make -C ./libft clean
	@make clean -C ${MLX_PATH} --no-print-directory

fclean:	clean
	rm -f ${NAME}
	rm -f ${NAME_BONUS}
	@make -C ./libft fclean
	@make clean -C ${MLX_PATH} --no-print-directory

re:	fclean all

.PHONY: all clean fclean re bonus
