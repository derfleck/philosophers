# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mleitner <mleitner@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 14:51:37 by mleitner          #+#    #+#              #
#    Updated: 2023/06/13 13:04:10 by mleitner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= philo_bonus
CC				:= cc
RM		    	:= rm -f
FLAGS			:= -Wall -Wextra -Werror
DEBUG			:= -g

SRCSDIR			:= ./src/
SRCSLIST		:= main.c \
					utils.c \
					init.c \
					process.c \
					routine.c
SRCS			:= $(addprefix ${SRCSDIR}, ${SRCSLIST})
BONUSSRCSLIST	:= ${SRCSLIST:.c=_bonus.c}
BONUSSRCS		:= $(addprefix ${SRCSDIR}, ${BONUSSRCSLIST})

OBJSDIR			:= ./obj/
OBJSLIST		:= ${SRCSLIST:.c=.o}
OBJS			:= $(addprefix ${OBJSDIR}, ${OBJSLIST})

BONUSOBJSLIST	:= ${BONUSSRCSLIST:.c=.o}
BONUSOBJS		:= $(addprefix ${OBJSDIR}, ${BONUSOBJSLIST})
HEADDIR			:= ./inc/

INCS			:= -I${HEADDIR} -pthread

${NAME}:		${OBJSDIR} ${OBJS}
				${CC} ${FLAGS} ${DEBUG} ${OBJS} -o ${NAME} ${INCS}

${OBJSDIR}%.o:	${SRCSDIR}%.c
				${CC} ${FLAGS} ${DEBUG} ${INCS} -c $< -o $@

${OBJSDIR}:
				mkdir -p ${OBJSDIR}

.PHONY:			all clean fclean re bonus test bonustest

all:			${NAME}

clean:
				${RM} -r ${OBJSDIR}

fclean:			clean
				${RM} ${NAME}
				${RM} ${BONUSNAME}

re:				fclean all

test:			all
				./${NAME} 1 800 200 200