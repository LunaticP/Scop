NAME = scop
SRC_NAME =	main.cpp\
		init.cpp\
		init_vertex_shader.cpp\
		init_fragment_shader.cpp\
		init_shader.cpp\
		read_glsl.cpp\
		perlin.cpp

INC_FILE = include/scop.h\
	   libft_scop

OBJ_NAME = $(SRC_NAME:.cpp=.o)
SRC_PATH = ./src/
OBJ_PATH = ./obj/
SRC=$(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ=$(addprefix $(OBJ_PATH),$(OBJ_NAME))

CC = g++ -g
OBJ_SUB =

INC=-I./include -I./libft_scop -I./libmatrix -I$(HOME)/CODE/external/glew/include/GL -I/usr/local/include/GLFW
ARG= -L./libft_scop/ -L/usr/lib64/ -L/usr/local/lib/
LIBS= -lft -ldl -lGLEW -lX11 -lGL -lGLU -lglfw -lXxf86vm -lXrandr -lpthread -lm
CFLAGS = -Wall -Werror
DEPDIR = .deps/
DEPFILES = $(patsubst %.cpp,$(DEPDIR)%.d,$(SRC_NAME))

all: $(NAME)
	@printf "\t\t\e[32m[OK]\e[0m\n"
$(DEPDIR)/%.d: $(SRC_PATH)%.cpp $(DEPDIR)%.d
	@mkdir -p $(DEPDIR)
	@$(CC) $(CFLAGS) $(INC) -MM -MT $(DEPDIR)$(patsubst %.cpp,$(DEPDIR)%.d,$(notdir $@)) $< -MF $@

-include $(DEPFILES)

$(NAME): lib print_rt $(OBJ)
	@$(CC) -g -O0 $(CFLAGS) $(ARG) $(INC) $(OBJ) $(LIBS) -o $@
lib:
	@make -C ./libft_scop
	@make -C ./libmatrix

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp $(INC_FILE)
	-@mkdir -p $(OBJ_PATH) $(addprefix $(OBJ_PATH),$(OBJ_SUB))
	@$(CC) $(CFLAGS) -c -o $@ $< $(INC)

clean:
	-@rm -rf $(OBJ_PATH) $(DEPDIR)
	@make -C ./libft_scop $@
	@make -C ./libmatrix $@
	@printf "\e[33mobjects\t\t\e[31m[CLEAN]\e[0m\n"

fclean: clean
	-@rm $(NAME)
	@make -C ./libft_scop $@
	@make -C ./libmatrix $@
	@printf "\e[33mrtvocl\t\t\e[31m[CLEAN]\e[0m\n"

re: fclean all

print_rt:
	@printf "\e[33mscop"

.PHONY: fclean clean
