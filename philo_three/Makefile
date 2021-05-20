# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mturquin <mturquin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/22 21:39:48 by mturquin          #+#    #+#              #
#    Updated: 2021/05/20 14:20:33 by mturquin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo_three

SRCS	:=	$(addprefix srcs/,\
			ft_philo_three.c\
			ft_inicialization.c\
			ft_dinner.c\
			ft_utils.c\
			ft_atoi.c\
			ft_isdigit.c\
			ft_strlen.c)

HEADER	:=	$(addprefix includes/,\
			philosophers.h\)

ALLOBJS	=	${SRCS}

CC		=	gcc -g -Wall -Wextra -Werror -Iincludes

all		:	$(NAME)

%.o		:	%.c $(HEADER)

$(NAME)	:	${ALLOBJS}
			$(CC) -o $(NAME) ${ALLOBJS}
clean:
			make fclean -C

fclean:		clean
			-rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re