# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/07 02:18:15 by ygaude            #+#    #+#              #
#    Updated: 2017/06/02 15:54:52 by ygaude           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
	  ft_isprint.c ft_isspace.c ft_itoa.c ft_lstadd.c ft_lstaddend.c           \
	  ft_lstdel.c ft_lstdelone.c ft_lstdelthis.c ft_lstend.c ft_lstiter.c      \
	  ft_lstmap.c ft_lstnew.c ft_magnitude.c ft_memalloc.c ft_memccpy.c        \
	  ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c \
	  ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c    \
	  ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_strappend.c ft_strcat.c     \
	  ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c  \
	  ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c         \
	  ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c           \
	  ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c          \
	  ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c          \
	  ft_toupper.c ft_strnlen.c

OBJ = ${SRC:c=o}

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS)	-c -o $@ $^

$(NAME): $(OBJ)
	@echo "Creating library..."
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "Done !"

clean:
	@rm -f $(OBJ)
	@echo "Object files removed."

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME) removed"

re: fclean all
