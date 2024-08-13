# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/03 18:19:18 by fmaqdasi          #+#    #+#              #
#    Updated: 2024/08/13 19:02:26 by fmaqdasi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -framework OpenGL -framework AppKit
# sudo apt install libc++-15-dev libc++abi-15-dev
NAME        := fractol
CC          := cc
CFLAGS       := -Wall -Wextra -Werror -g3 -fsanitize=address
RM		    := rm -f
# INCLUDE =  -Ilibft/ -Iminilibx/
# LIBFT_DIR = libft/
MINILIBX_DIR = minilibx-linux/
MINILIBX = minilibx-linux/libmlx.a
# LIBFT = libft/libft.a

SRCS        := 				src/parsing_color_resolution_texture.c \
							src/parsing_map.c \
							src/parsing_utils.c \
							src/keys_draw.c \
							src/raycasting_init.c \
							src/raycasting_utils.c \
							src/raycasting_move.c \
							src/raycasting.c \
							src/sprites.c \
							src/errors.c \
							src/save.c \
							src/get_next_line.c \
							src/get_next_line_utils.c \
							src/init.c


SRCSM1       :=           src/parsing.c \


                          
OBJS        := $(SRCS:.c=.o)
OBJSNAME    := $(SRCSM1:.c=.o)

LIBS = -L$(LIBFT_DIR) $(LIBFT)
MINI = -L$(MINILIBX_DIR) $(MINILIBX)

.c.o:
	@${CC} ${CFLAGS} $(INCLUDE) -c $< -o $@
	
${NAME}:	${OBJS} ${OBJSNAME} $(LIBFT) $(MINILIBX)
			@${CC} ${CFLAGS} ${OBJS} ${OBJSNAME} $(LIBS) $(MINI) -lm -lX11 -lXext -o ${NAME} 
			@echo "\033[0;32mFractol compiled successfully"
# $(LIBFT):
# 	        @make -C $(LIBFT_DIR) -s
# 			@echo "\033[0;32mLibft compiled successfully"
			
$(MINILIBX):
	        @make -C $(MINILIBX_DIR) -s
			@echo "\033[0;32mMinilibx compiled successfully"

all:		${NAME}

clean:
			@${RM} *.o
			# @make -C $(LIBFT_DIR) clean -s
			@make -C $(MINILIBX_DIR) clean -s
			@echo "\033[0;31mObjects removed successfully"


fclean:		clean
			@${RM} ${NAME}
			# @make -C $(LIBFT_DIR) fclean -s
			@make -C $(MINILIBX_DIR) clean -s
			@echo "\033[0;31mAll created objects were removed successfully"

re:			fclean all
			@echo "\033[0;32mFractol was recompiled successfully"

.PHONY:		all clean fclean re bonus