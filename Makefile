# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/13 13:48:05 by lhorefto          #+#    #+#              #
#    Updated: 2021/08/19 17:33:04 by lhorefto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS				=	main.c utils.c pwd.c exec.c cd.c input.c \
					history.c minishell.c pipe.c env.c export.c operators.c \
					unset.c utils2.c redirect.c redirect_io.c quotes.c \
					quotes2.c extras.c\
					
SRCS_LINUX			= signalhandler_linux.c

SRCS_MAC			= signalhandler_mac.c

OBJS				= ${SRCS:.c=.o}
OBJS_LINUX			= ${SRCS_LINUX:.c=.o}
OBJS_MAC			= ${SRCS_MAC:.c=.o}

CC					= gcc
RM					= rm -f
CFLAGS				= -Wall -Wextra -Werror
UNAME_S				= $(shell uname -s)
MAKE_LIBFT			= @make -s --no-print-directory -C
LIBS				= -L ./libft -lft -lreadline
HEADERS				= minishell.h
LIBS_MAC			= -L/opt/homebrew/Cellar/readline/8.1/lib
NAME				= minishell

COMPILE_LINE_LINUX	= $(CC) $(CFLAGS) ${OBJ} $(LIBS) -o $(NAME)
COMPILE_LINE_MAC		= $(CC) $(CFLAGS) ${OBJ} $(LIBS) $(LIBS_MAC) -o $(NAME)

ifeq ($(UNAME_S),Linux)
	COMPILE			= $(COMPILE_LINE_LINUX)
	CROSS			= $(OBJS_LINUX)
endif
ifeq ($(UNAME_S),Darwin)
	COMPILE			= $(COMPILE_LINE_MAC)
	CROSS			= $(OBJS_MAC)
	@READLINE		= @brew install readline
endif

OBJ					= ${CROSS} ${OBJS} 

$(NAME):	${OBJ}
			$(MAKE_LIBFT) ./libft bonus
			$(READLINE)
			$(COMPILE)

all:				$(NAME)

clean:
					$(MAKE_LIBFT) ./libft clean
					$(RM) $(OBJ) $(BONUS_OBJS)

fclean:				clean
					$(MAKE_LIBFT) ./libft fclean
					$(RM) $(NAME)

re:					fclean $(NAME)

