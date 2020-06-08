
# -L <library dir> : select directory to find library
# 	링크할 라이브러리를 명시해주는 옵션
# 	libft.a 라이브러리에서  lib 와 .a 를 제외한 이름을 붙여준다.
# -l <library dir> : selet to link library
# -I<hederfile dir> : find header file in selected dir when compile source code
# 	"" 으로 헤더파일을 include 할때 헤더파일의 경로를 정해준다.
# 	wrong : -I <dir>
# 	right	: -I<dir>
# $(addprefix prefix,names...)
# 	매개변수 names는 공백문자들로 구분된, 일단의 이름들로 취급된다; prefix는 유닛으로써 사용된다. 
# 	prefix의 값은 각 개별 이름의 앞에 붙고, 그들 사이에 단일 스페이스들로 채워 연결된 더 커다란 이름들이 결과이다. 
# 	예를 들어서,
# 	$(addprefix src/,foo bar)
# 		는 `src/foo src/bar'라는 결과를 만든다.

CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit
LIBX_FLAGS = -Ilib/minilibx_mms_20200219_beta -L lib/minilibx_mms_20200219_beta
LIBFT_FLAGS = -lft -L./lib/libft 
NAME = miniRT

COLOR_SRC = \
			color_utils_1.c \
			color_utils_2.c
COLOR_SRC_DIR = ./srcs/color

ERROR_SRC = \
			error.c
ERROR_SRC_DIR = ./srcs/error

PARSING_SRC = \
			parsing_objects.c \
			parsing_options.c \
			parsing_utils_1.c \
			parsing_utils_2.c \
			parsing_utils_3.c \
			parsing.c
PARSING_SRC_DIR = ./srcs/parsing

SHADER_SRC = \
			shader.c \
			vertex_shader.c \
			pixel_shader.c \
			shader_utils.c \
			intersect_cylinder.c \
			intersect_plane.c \
			intersect_sphere.c \
			intersect_square.c \
			intersect_triangle.c \
			intersection_controller.c \
			intersection_utils.c \
			make_normal.c
SHADER_SRC_DIR = ./srcs/shader

VECTOR_SRC = \
			vector_utils.c \
			vector_arithmetic_operation.c \
			vector_product_normal.c
VECTOR_SRC_DIR = ./srcs/vector

INC = -I./include
SRCS_LIST =  \
		$(addprefix $(PARSING_SRC_DIR)/, $(PARSING_SRC)) \
		$(addprefix $(ERROR_SRC_DIR)/, $(ERROR_SRC)) \
		$(addprefix $(SHADER_SRC_DIR)/, $(SHADER_SRC)) \
		$(addprefix $(VECTOR_SRC_DIR)/, $(VECTOR_SRC)) \
		$(addprefix $(COLOR_SRC_DIR)/, $(COLOR_SRC)) \
		./srcs/main.c
		# ./srcs/test.c
OBJS = $(SRCS_LIST:%c.=%.o)
all: $(NAME)


# link libft.a and minilibx library
# -o : rename a.out to $(NAME)
$(NAME): $(OBJS)
	$(MAKE) -C lib/libft bonus
	$(CC) -g $(CFLAGS) $(LIBX_FLAGS) $(LIBFT_FLAGS) $(INC) $(SRCS_LIST) $(MLX_FLAGS) -o $(NAME)

clean :
	$(MAKE) -C lib/libft clean
	rm $(NAME)

norminette :
	norminette $(SRCS_LIST)

fclena : clean all