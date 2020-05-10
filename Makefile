
# -L <library dir> : select directory to find library
# -I <library dir> : selet to link library

NAME = miniRT

$(NAME) :
	gcc -I ./lib/minilibx_mms_20200219_beta main.c \
	-L ./lib/minilibx_mms_20200219_beta -lmlx -framework OpenGL -framework AppKit