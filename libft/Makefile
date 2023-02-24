# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ychun <ychun@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/25 01:30:14 by ychun             #+#    #+#              #
#    Updated: 2023/01/25 01:30:17 by ychun            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADERS = /.
SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c
OBJ = $(SRC:.c=.o)
NAME = libft.a
CC = gcc
FLAGS = -Wall -Wextra -Werror
LIBC = ar rc
LIBR = ranlib
RM = rm -f

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o} -I ${HEADERS}

${NAME}: ${OBJ}
		${LIBC} ${NAME} ${OBJ}
		${LIBR} ${NAME}

all: ${NAME}

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all
