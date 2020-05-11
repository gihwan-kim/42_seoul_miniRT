# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/07 15:47:23 by gihkim            #+#    #+#              #
#    Updated: 2020/05/11 15:47:38 by gihwan-kim       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_NO_B = \
			./srcs/ft_atoi.c \
			./srcs/ft_bzero.c \
			./srcs/ft_calloc.c \
			./srcs/ft_isalnum.c \
			./srcs/ft_isalpha.c \
			./srcs/ft_isascii.c \
			./srcs/ft_isdigit.c \
			./srcs/ft_isprint.c \
			./srcs/ft_itoa.c \
			./srcs/ft_memccpy.c \
			./srcs/ft_memchr.c \
			./srcs/ft_memcmp.c \
			./srcs/ft_memcpy.c \
			./srcs/ft_memmove.c \
			./srcs/ft_memset.c \
			./srcs/ft_putchar_fd.c \
			./srcs/ft_putendl_fd.c \
			./srcs/ft_putnbr_fd.c \
			./srcs/ft_putstr_fd.c \
			./srcs/ft_split.c \
			./srcs/ft_strchr.c \
			./srcs/ft_strdup.c \
			./srcs/ft_strjoin.c \
			./srcs/ft_strlcat.c \
			./srcs/ft_strlcpy.c \
			./srcs/ft_strlen.c \
			./srcs/ft_strmapi.c \
			./srcs/ft_strncmp.c \
			./srcs/ft_strnstr.c \
			./srcs/ft_strrchr.c \
			./srcs/ft_strtrim.c \
			./srcs/ft_substr.c \
			./srcs/ft_tolower.c \
			./srcs/ft_toupper.c

SRC_B = \
		./srcs/ft_lstadd_back.c \
		./srcs/ft_lstadd_front.c \
		./srcs/ft_lstclear.c \
		./srcs/ft_lstdelone.c \
		./srcs/ft_lstiter.c \
		./srcs/ft_lstlast.c \
		./srcs/ft_lstmap.c \
		./srcs/ft_lstnew.c \
		./srcs/ft_lstsize.c

OBJS_NO_B = $(SRC_NO_B:%.c=%.o)
OBJS_B = $(SRC_B:%.c=%.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I include
NAME = libft.a

ifdef CHECK_BONUS
	OBJS = $(OBJS_NO_B) $(OBJS_B)
else
	OBJS = $(OBJS_NO_B)
endif

all : $(NAME)

$(NAME) : $(OBJS)
	ar rcs $(NAME) $(OBJS)
	# ranlib $(NAME)

clean :
	rm -f $(OBJS) $(NAME) *.o

fclean : clean all

re : fclean all

bonus :
	make CHECK_BONUS=1 all