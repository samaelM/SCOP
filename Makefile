NAME				=	SCOP

CC					=	c++
CFLAGS				=	-Wall -Werror -Wextra -g3
CFLAGS_TEMP			=	-g3

INCS				=	app/Graphics/Graphics.hpp\
						app/Parser/Parser.hpp\
						app/Parser/Data.hpp\
						app/Window/Window.hpp\
						app/utils/utils.hpp\
						ressources/lib/glad/include/glad/glad.h\

SRCS				=	app/main.cpp\
						app/Window/Window.cpp\
						app/Parser/Parser.cpp\
						app/Graphics/Mesh.cpp\
						app/Graphics/Shader.cpp\
						app/Graphics/Texture.cpp\

OBJS_DIR			=	obj
OBJS				=	${SRCS:%.cpp=${OBJS_DIR}/%.o}

GLAD				=	${OBJS_DIR}/lib/glad/libglad.a

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
	@${CC} $(CFLAGS_TEMP) ${OBJS} ${GLAD} -o ${NAME}
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

${GLAD}:
	@cmake -S ressources/lib/glad -B ${OBJS_DIR}/lib/glad -Wno-dev
	@cmake --build ${OBJS_DIR}/lib/glad

clean:
	rm -rf ${NAME}

fclean: clean
	rm -rf ${OBJS_DIR}

re: fclean all

.PHONY: all clean fclean re
