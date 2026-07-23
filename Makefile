NAME				=	SCOP

CC					=	c++
CFLAGS				=	-Wall -Werror -Wextra -g3
CFLAGS_TEMP				=	-g3

INCS				=	app/Graphics/Graphics.hpp\
						app/Parser/Parser.hpp\
						app/Window/Window.hpp\

SRCS				=	app/main.cpp\

OBJS_DIR			=	obj
OBJS				=	${SRCS:%.cpp=${OBJS_DIR}/%.o}

#COLORS
RED					=	\033[0;31m
GREEN				=	\033[0;32m
YELLOW				=	\033[0;33m
WHITE				=	\033[0m
BOLD				=	\033[1m
FLASH				=	\033[6m
RESET				=	\033[0m
BANDE				=	\033[7m
RETURN				=	\033[2K\r

#RULES
${NAME}:all

all: ${OBJS}
	@printf "${RETURN}${RED}[COMPILING 🛞 ]${WHITE}${NAME} :"
	@${CC} ${OBJS} $(CFLAGS_TEMP) -o ${NAME}
	@printf "${RETURN}${GREEN}[DONE! ✅]${WHITE}${NAME}\n"
	@printf "${RED}${BOLD}   ____________  \n"
	@printf "  (  COMPILED! ) \n"
	@printf "    ͞ v ͞ ͞ ͞ ͞ ͞ ͞ ͞ ͞ \n"
	@printf "   /\/\ \n"
	@printf "  ( ${FLASH}o${RED}${BOLD}w${FLASH}o${RED}${BOLD})\n"
	@printf "  / >*<\ \n"

${OBJS_DIR}/%.o: %.cpp
	@mkdir -p ${dir $@}
	@printf "${RETURN}${RED}[COMPILING 🛞 ]${WHITE}$< :"
	@${CC} $(CFLAGS_TEMP) -c -o $@ $<
	@printf "${RETURN}${GREEN}[DONE! ✅]${WHITE}$<\n"

clean:
	rm ${NAME}

fclean: clean
	rm -rf ${OBJS_DIR}

re: fclean all

.PHONY: all clean fclean re
