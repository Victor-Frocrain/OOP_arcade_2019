##
## EPITECH PROJECT, 2020
## arcade
## File description:
## arcade: lib/SDL/Makefile
##

NAME_SDL=	../lib_arcade_SDL.so

SRC_SDL	=	src/SDL.cpp						\
			../../src/ArcadeException.cpp	\
			../../src/FileReader.cpp		\
			../../src/ArcadeUtils.cpp		\
			../../src/AEntity.cpp			\
			../../src/Entity.cpp			\

OBJ_SDL	=	$(SRC_SDL:%.cpp=%.o)

CXXFLAGS=	-W -Wall -Wextra -Wshadow -std=c++11 -I include/ -I ../../include -fPIC

LDFLAGS	= 	-shared -lSDL2 -lSDL2_ttf

CXX		=	g++

all:		$(NAME_SDL)

$(NAME_SDL):$(OBJ_SDL)
			$(CXX) -o $(NAME_SDL) $(OBJ_SDL) $(LDFLAGS)

clean:
			$(RM) $(OBJ_SDL)

fclean:		clean
			$(RM) $(NAME_SDL)

re:			fclean all

.PHONY:		clean fclean re
