# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/27 17:07:31 by vmercadi          #+#    #+#              #
#    Updated: 2018/04/24 18:08:05 by vmercadi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

SRC =	srcs/error.c 		srcs/event.c		srcs/maintest2.c \
		srcs/vect_calc1.c	srcs/vect_calc2.c 	srcs/vect_utils.c \
		srcs/utils.c		srcs/init.c			srcs/intersections.c \
		srcs/color.c		srcs/lux.c			srcs/scene.c \
		srcs/matrice.c		srcs/cam.c			srcs/vector.c \
		srcs/to_fdf.c		srcs/obj.c			srcs/calc_obj.c \
		srcs/action.c		srcs/event_obj.c	srcs/parsing.c \
		srcs/help.c			srcs/color_calc.c	srcs/color_utils.c \
		srcs/event_move.c	srcs/init_obj.c		srcs/init_data.c \
		srcs/init_sheit.c	srcs/parse_utils.c	srcs/lux_calc.c \
		srcs/draw.c			srcs/event_screen.c	srcs/UI_main.c \
		srcs/UI_init.c		srcs/UI_button.c	srcs/UI_error.c \
		srcs/UI_help.c		srcs/UI_onglet.c	srcs/UI_input.c \
		srcs/UI_id.c

INCLUDES	= -I includes -I libft
CFLAGS		= -Wall -Wextra -Werror $(INCLUDES)
MFLAGS		= -lpthread -O3 -flto -march=native
SRCO		= $(SRC:%.c=%.o)
LIB			= lib/libft/libft.a
H			= includes/rtv1.h includes/color.h includes/ui.h includes/utils.h
SDL2LIB		= $(shell sdl2-config --libs)
SDL2CFLAGS	= $(shell sdl2-config --cflags)
SDL2TTFLIB	= -lSDL2_ttf

#Install imagemagick to convert screenshots
MAGICK := $(shell ls ~/.brew/lib/ | grep libMagick)
#Installing SDL2_ttf and SDL2_image and move SDL2 if necessary
SDL_SDL := $(shell ls ~/Library/Frameworks | grep SDL2)
SDL_IMG := $(shell ls ~/.brew/lib/ | grep libSDL2_image.a)
SDL_TTF := $(shell ls ~/.brew/lib/ | grep libSDL2_ttf.a)
#Name for videos
TIME := $(shell date | cut -c5- | rev | cut -c11- | rev | tr ' ' '_')
ifeq ($(SDL_TTF), "")
    SDL_TTF_INST := "brew install"
else
    SDL_TTF_INST := "echo"
endif

ifeq ($(SDL_IMG), "")
    SDL_IMG_INST := "brew install"
else
    SDL_IMG_INST := "echo"
endif

ifeq ($(MAGICK), "")
    MAGIK_INST := "brew install"
else
    MAGIK_INST := "echo"
endif

.PHONY: all re cleans

all: $(NAME)

$(NAME): $(SDL_SDL) $(SDL_IMG) $(SDL_TTF) $(MAGICK) $(H) $(SRCO)
	@mkdir -p /tmp/Screenshots
	@make -s -C lib/libft/
	@echo "\033[32;4mLIBFT\x1b[0m	\033[32;7mcompiled\x1b[0m"
	@gcc $(CFLAGS) $(SDL2CFLAGS) $(LIB) -o $(NAME) $(SRC) $(MFLAGS) $(SDL2LIB) $(SDL2TTFLIB)
	# @gcc $(LIB) $(MFLAGS) $(SDL2LIB) $(SDL2TTFLIB) $(SRCO) -o $(NAME)
	@echo "\033[32;4mRTV1\x1b[0m	\033[32;7mcompiled\x1b[0m"
	@echo "\033[32;3m-----------------------------------"
	@echo "Things went great ! For this time.."
	@echo "-----------------------------------\x1b[0m"

# sdl2lib:
# 	$(eval SDL2LIB = $(shell sdl2-config --libs))
# sdl2cflags:
# 	$(eval SDL2CFLAGS = $(shell sdl2-config --cflags))

# %.o: %.c
# 	@gcc $(CFLAGS) $(SDL2CFLAGS) $^ -o $@

$(SDL_SDL):
	$(shell mkdir -p ~/library/Frameworks | cp -rf ./lib/SDL2/ ~/library/Frameworks)

$(SDL_IMG):
	$(SDL_IMG_INST) SDL2_image

$(SDL_TTF):
	$(SDL_TTF_INST) SDL2_ttf

$(MAGICK):
	$(MAGIK_INST) imagemagick

film:
	@mkdir -p /tmp/Screenshots/videos
	@brew install ffmpeg
	@find /tmp/Screenshots/ -type f -name '*.bmp' -exec convert {} {}.jpg \;
	@ffmpeg -r 25 -f image2 -s 960x720 -i /tmp/Screenshots/Screenshot%d.bmp.jpg \
	-vcodec libx264 -crf 25  -pix_fmt yuv420p /tmp/Screenshots/videos/$(TIME).mp4
	@rm /tmp/Screenshots/*.bmp
	@echo "\033[32;3mA video have been created in /tmp/Screenshots/videos/ !\x1b[0m"

cleanfilm:
	@rm -rf /tmp/Screenshots

it: all
	@./RTv1

clean:
	@rm -rf $(SRCO)
	@make clean -s -C lib/libft/

fclean: clean cleanfilm
	@rm -rf $(NAME)
	@echo "\033[32;3mEverything have been DESTROYED !\x1b[0m"

re: fclean all

ultra: all clean

reit: re clean
	@./RTv1
