# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/01 10:39:56 by acoezard          #+#    #+#              #
#    Updated: 2022/04/01 12:49:54 by acoezard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_SERV	:=	ircserv
NAME_BOT	:=	ircbot
VERSION		:=	1.0
ARCH		:=	x64

# -----------------------------------------------------------------------------
# COMPILATION
# -----------------------------------------------------------------------------
SRCS_SERV	:=	Utils.cpp \
				Console.cpp \
				server/main.cpp \
				server/Server.cpp \
				server/Channel.cpp \
				server/cmds/PassCommand.cpp \
				server/cmds/UserCommand.cpp \
				server/cmds/NickCommand.cpp \
				server/cmds/JoinCommand.cpp \
				server/cmds/PrivmsgCommand.cpp \
				server/cmds/QuitCommand.cpp \
				server/cmds/TopicCommand.cpp \
				server/cmds/PartCommand.cpp \
				server/cmds/ModeCommand.cpp \
				server/cmds/PingCommand.cpp \
				server/cmds/MotdCommand.cpp \
				server/cmds/VersionCommand.cpp \
				server/cmds/TimeCommand.cpp \
				server/cmds/InviteCommand.cpp \
				server/cmds/OperCommand.cpp \
				server/cmds/ListCommand.cpp \
				server/cmds/KickCommand.cpp \
				server/cmds/NamesCommand.cpp

OBJS_SERV	:=	$(addprefix bin/, $(SRCS_SERV:.cpp=.o))

SRCS_BOT	:=	Utils.cpp \
				Console.cpp \
				bot/main.cpp \
				bot/Bot.cpp

OBJS_BOT	:=	$(addprefix bin/, $(SRCS_BOT:.cpp=.o))

CC			:=	clang++
CFLAGS		:=	-Wall -Wextra -Werror -std=c++98

# -----------------------------------------------------------------------------
# COLORS
# -----------------------------------------------------------------------------
__RED		:=	"\033[1;31m"
__GREEN		:=	"\033[1;32m"
__YELLOW	:=	"\033[1;33m"
__BLUE		:=	"\033[1;36m"
__WHITE		:=	"\033[1;37m"
__EOC		:=	"\033[0;0m"

# -----------------------------------------------------------------------------
# RULES
# -----------------------------------------------------------------------------
bin/%.o: srcs/%.cpp
	@mkdir -p ${dir $@}
	@${CC} ${CFLAGS} -o $@ -c $< -I includes
	@echo ${__GREEN}"Compiling "${__WHITE}$<${__EOC}

all: ${NAME_SERV}

${NAME_SERV}: ${OBJS_SERV}
	@${CC} ${CFLAGS} ${OBJS_SERV} -o ${NAME_SERV}
	@echo ${__GREEN}"Finished "${__WHITE}${NAME_SERV}" v"${VERSION}" bin target"${__EOC}

${NAME_BOT}: ${OBJS_BOT}
	@${CC} ${CFLAGS} ${OBJS_BOT} -o ${NAME_BOT}
	@echo ${__GREEN}"Finished "${__WHITE}${NAME_BOT}" v"${VERSION}" bin target"${__EOC}

bonus: ${NAME_BOT}

run: ${NAME_SERV}
	./${NAME_SERV} 6667 test
run-bonus: ${NAME_BOT}
	./${NAME_BOT} 127.0.0.1 6667 test general

clean:
	@rm -rf bin/

fclean: clean
	@rm -rf ${NAME_SERV} ${NAME_BOT}
	@echo ${__BLUE}"Cleaned "${__WHITE}"bin target(s)"${__EOC}

re: fclean all
re-all: fclean ${NAME_SERV} ${NAME_BOT}

.PHONY: all fclean clean re
