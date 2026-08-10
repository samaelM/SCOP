NAME			:=	SCOP

CXX				:=	c++
CC				:=	cc
AR				:=	ar rcs
RM				:=	rm -rf

INC_DIR			:=	app ressources/lib/glad/include
OBJ_DIR			:=	obj

CXXFLAGS		:=	-Wall -Werror -Wextra -std=c++17 -g3 $(addprefix -I, $(INC_DIR)) -MMD -MP
CFLAGS			:=	-Wall -Werror -Wextra -g3 $(addprefix -I, $(INC_DIR)) -MMD -MP
LDLIBS			:=	-lglfw

SRCS			:=	app/main.cpp \
					app/Window/Window.cpp \
					app/Parser/Parser.cpp \
					app/Graphics/Mesh.cpp \
					app/Graphics/Shader.cpp \
					app/Graphics/Texture.cpp

GLAD_SRC		:=	ressources/lib/glad/src/glad.c

OBJS			:=	$(SRCS:%.cpp=$(OBJ_DIR)/%.o)
OBJ_GLAD		:=	$(GLAD_SRC:%.c=$(OBJ_DIR)/%.o)
DEPS			:=	$(OBJS:%.o=%.d) $(OBJ_GLAD:%.o=%.d)

GLAD_LIB		:=	$(OBJ_DIR)/ressources/lib/glad/libglad.a

RED				:=	\033[0;31m
GREEN			:=	\033[0;32m
YELLOW			:=	\033[0;33m
WHITE			:=	\033[0m
BOLD			:=	\033[1m
FLASH			:=	\033[6m
RETURN			:=	\033[2K\r

all: $(NAME)

$(NAME): $(OBJS) $(GLAD_LIB)
	@printf "$(RETURN)$(RED)[LINKING 🛞 ]$(WHITE) $@ :"
	@$(CXX) $(CXXFLAGS) $(OBJS) $(GLAD_LIB) $(LDLIBS) -o $@
	@printf "$(RETURN)$(GREEN)[DONE! ✅]$(WHITE) $@\n"
	@printf "$(RED)$(BOLD)   ____________  \n"
	@printf "  (  COMPILED! ) \n"
	@printf "    ͞ v ͞ ͞ ͞ ͞ ͞ ͞ ͞ ͞ \n"
	@printf "   /\\/\\ \n"
	@printf "  ( $(FLASH)o$(RED)$(BOLD)w$(FLASH)o$(RED)$(BOLD))\n"
	@printf "  / >*<\\ \n$(RESET)"

$(GLAD_SRC):
	@bash ./setup.sh

$(GLAD_LIB): $(GLAD_SRC) $(OBJ_GLAD)
	@mkdir -p $(dir $@)
	@$(AR) $@ $(OBJ_GLAD)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@printf "$(RETURN)$(RED)[COMPILING 🛞 ]$(WHITE) $< :"
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@printf "$(RETURN)$(GREEN)[DONE! ✅]$(WHITE) $< -> $@\n"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "$(RETURN)$(RED)[COMPILING 🛞 ]$(WHITE) $< :"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(RETURN)$(GREEN)[DONE! ✅]$(WHITE) $< -> $@\n"

-include $(DEPS)

clean:
	@$(RM) $(OBJ_DIR)
	@printf "$(YELLOW)[CLEANED] Object directory removed.$(WHITE)\n"

fclean: clean
	@$(RM) $(NAME)
	@printf "$(YELLOW)[CLEANED] Binary removed.$(WHITE)\n"

re: fclean all

.PHONY: all clean fclean re
