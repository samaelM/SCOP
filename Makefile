NAME				=	SCOP

CC					=	c++
CFLAGS				=	-Wall -Werror -Wextra -g3 -I ressources/lib/glad/include -lglfw 
CFLAGS_TEMP			=	-g3 -I ressources/lib/glad/include -lglfw 

INCS				=	app/Graphics/Graphics.hpp\
						app/Parser/Parser.hpp\
						app/Window/Window.hpp\
						app/utils/utils.hpp\
						ressources/lib/glad/include/glad/glad.h\

SRCS				=	app/main.cpp\
						app/Window/Window.cpp\
						app/Parser/Parser.cpp\
						app/Graphics/Mesh.cpp\
						app/Graphics/Shader.cpp\
						app/Graphics/Texture.cpp


OBJS_DIR			=	obj
OBJS				=	${SRCS:%.cpp=${OBJS_DIR}/%.o}

GLAD				=	${OBJS_DIR}/ressources/lib/glad/libglad.a

SRCS_GLAD			=	ressources/lib/glad/src/glad.c
OBJS_GLAD			=	${SRCS_GLAD:%.c=${OBJS_DIR}/%.o}

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

all: ${GLAD} ${OBJS}
	@printf "${RETURN}${RED}[COMPILING 🛞 ]${WHITE}${NAME} :"
	@${CC} $(CFLAGS) ${OBJS} ${GLAD} -o ${NAME}
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
	@${CC} $(CFLAGS) -c -o $@ $<
	@printf "${RETURN}${GREEN}[DONE! ✅]${WHITE}$< -> $@\n"

${GLAD}: ${OBJS_GLAD}
	ar -rc ${GLAD} ${OBJS_GLAD}

${OBJS_DIR}/%.o: %.c
	@mkdir -p ${dir $@}
	@printf "${RETURN}${RED}[COMPILING 🛞 ]${WHITE}$< :"
	@${CC} $(CFLAGS) -c -o $@ $<
	@printf "${RETURN}${GREEN}[DONE! ✅]${WHITE}$< -> $@\n"

clean:
	rm -rf ${NAME}

fclean: clean
	rm -rf ${OBJS_DIR}

re: fclean all

.PHONY: all clean fclean re
