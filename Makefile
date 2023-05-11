# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 14:51:37 by mleitner          #+#    #+#              #
#    Updated: 2023/04/06 12:36:14 by mleitner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= philosophers
BONUSNAME		:= philosophers_bonus
CC				:= cc
RM		    	:= rm -f
FLAGS			:= -Wall -Wextra -Werror
DEBUG			:= -g

SRCSDIR			:= ./src/
SRCSLIST		:= main.c \
					utils.c \
					init.c \
					threads.c \
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

${BONUSNAME}:	${OBJSDIR} ${BONUSOBJS}
				${CC} ${FLAGS} ${DEBUG} ${BONUSOBJS} -o ${BONUSNAME} ${INCS}

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

bonus:			${BONUSNAME}

test:			all
				./${NAME} 1 800 200 200