# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/12 18:07:46 by dbouron           #+#    #+#              #
#    Updated: 2022/10/21 11:53:40 by dbouron          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
HEADFILE = libft.h

SRC = ft_bzero.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_memcmp.c \
	ft_memmove.c ft_strchr.c ft_strlcat.c ft_strlen.c ft_strnstr.c \
	ft_tolower.c ft_atoi.c ft_atoi_base.c ft_calloc.c ft_isalpha.c \
	ft_isdigit.c ft_memchr.c ft_memcpy.c ft_memset.c ft_strdup.c \
	ft_strlcpy.c ft_strncmp.c ft_strrchr.c ft_toupper.c ft_substr.c \
	ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
	ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

SRC_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS = $(SRC:.c=.o)

OBJS_BONUS = $(SRC_BONUS:.c=.o)

%.o: %.c $(HEADFILE)
	gcc -Wall -Werror -Wextra -o $@ -c $<

$(NAME) : $(OBJS)
	ar rc $(NAME) $(OBJS)

all : $(NAME)

bonus : $(OBJS_BONUS)
	ar rc $(NAME) $(OBJS_BONUS)

clean :
	rm -rf $(OBJS) $(OBJS_BONUS)

fclean : clean
	rm -rf $(NAME)

re : fclean all