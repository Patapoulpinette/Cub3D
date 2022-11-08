# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/03 14:53:19 by dbouron           #+#    #+#              #
#    Updated: 2022/11/08 15:38:24 by apercebo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
NAME_BONUS = cub3d_bonus

# **************************************************************************** #
#                               FILES and PATHS                                #
# **************************************************************************** #

MINILIBX = ./minilibx_opengl

LIBFT = ./libft
LIBFT_EXEC = ./libft/libft.a

SRCS =	$(shell find mandatory/sources -name "*.c")
SRCS +=	$(shell find GNL -name "*.c")
HEADFILE = $(shell find mandatory/includes -name "*.h")
HEADFILE += $(shell find GNL -name "*.h")
HEADFILE += $(shell find libft -name "*.h")
HEADFILE += $(shell find minilibx_opengl -name "*.h")

SRCS_BONUS =	$(shell find bonus/sources -name "*.c")
SRCS_BONUS +=	$(shell find GNL -name "*.c")
HEADFILE_BONUS = $(shell find bonus/includes -name "*.h")
HEADFILE_BONUS += $(shell find GNL -name "*.h")
HEADFILE_BONUS += $(shell find libft -name "*.h")
HEADFILE_BONUS += $(shell find minilibx_opengl -name "*.h")

CFLAGS = -Wall -Wextra -Werror
CFLAGS += -I mandatory/includes/ -I libft/ -I minilibx_opengl/ -I GNL/ -O3
#CFLAGS += -fsanitize=address -g3

CFLAGS_BONUS = -Wall -Wextra -Werror
CFLAGS_BONUS += -I bonus/includes/ -I libft/ -I minilibx_opengl/ -I GNL/ -O3
#CFLAGS_BONUS += -fsanitize=address -g3

# **************************************************************************** #
#                                    COLORS                                    #
# **************************************************************************** #

BLACK			=	\033[0;30m
RED				=	\033[0;31m
GREEN			=	\033[0;32m
ORANGE			=	\033[0;33m
BLUE			=	\033[0;34m
PURPLE			=	\033[0;35m
CYAN			=	\033[0;36m
LIGHT_GRAY		=	\033[0;37m
DARK_GRAY		=	\033[1;30m
LIGHT_RED		=	\033[1;31m
LIGHT_GREEN		=	\033[1;32m
YELLOW			=	\033[1;33m
LIGHT_BLUE		=	\033[1;34m
LIGHT_PURPLE	=	\033[1;35m
LIGHT_CYAN		=	\033[1;36m
WHITE			=	\033[1;37m
NO_COLOR		=	\033[0m

# **************************************************************************** #
#                              COMMANDS and RULES                              #
# **************************************************************************** #

.SILENT:

.DEFAULT_GOAL = all

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all : compile_minilibx compile_libft $(NAME)

bonus : compile_minilibx compile_libft $(NAME_BONUS)

mandatory/sources/%.o: mandatory/sources/%.c $(HEADFILE) Makefile
	gcc $(CFLAGS) -o $@ -c $<
	@printf "\r$(LIGHT_GRAY)Loading...$(NO_COLOR)"

bonus/sources/%.o: bonus/sources/%.c $(HEADFILE_BONUS) Makefile
	gcc $(CFLAGS_BONUS) -o $@ -c $<
	@printf "\r$(LIGHT_GRAY)Loading bonus...$(NO_COLOR)"

$(NAME) : $(OBJS) $(HEADFILE) $(LIBFT_EXEC)
	gcc $(CFLAGS) -o $(NAME) $(LIBFT_EXEC) $(SRCS) -L minilibx_opengl -lmlx -framework OpenGL -framework AppKit -lm
	@printf "\r$(LIGHT_GREEN)➞$(NO_COLOR) Compiled $(LIGHT_GREEN)✔$(NO_COLOR)\n"

$(NAME_BONUS) : $(OBJS_BONUS) $(HEADFILE_BONUS) $(LIBFT_EXEC)
	gcc $(CFLAGS_BONUS) -o $(NAME_BONUS) $(LIBFT_EXEC) $(SRCS_BONUS) -L minilibx_opengl -lmlx -framework OpenGL -framework AppKit -lm
	@printf "\r$(LIGHT_GREEN)➞$(NO_COLOR) Compiled with bonus $(LIGHT_GREEN)✔$(NO_COLOR)\n"

compile_minilibx :
	@make -C $(MINILIBX)

compile_libft :
	@make -C $(LIBFT)

git :
	@git add .
	@printf "Message of the commit: " && read msg && git commit -m "$$msg"
	@git push

clean :
	rm -rf $(OBJS)
	rm -rf $(OBJS_BONUS)
	@make clean -C $(MINILIBX)
	@make clean -C $(LIBFT)
	@printf "\r$(LIGHT_BLUE)➞$(NO_COLOR) Cleaned $(LIGHT_BLUE)✔$(NO_COLOR)\n"

fclean : clean
	rm -rf $(NAME)
	rm -rf $(NAME_BONUS)
	@make clean -C $(MINILIBX)
	@make fclean -C $(LIBFT)

re : fclean all

.PHONY: all bonus compile_minilibx compile_libft git clean fclean re
