##
## EPITECH PROJECT, 2020
## Arcade:
## File description:
## Arcade: games/pacman/Makefile
##

NAME	=	../lib_arcade_pacman.so

SRC 	=	src/Pacman.cpp					\
			src/APacman.cpp					\
			src/APacmanScore.cpp			\
			../../src/ArcadeUtils.cpp		\
			../../src/AEntity.cpp			\
			../../src/Entity.cpp			\
			../../src/ArcadeException.cpp	\
			../../src/AGame.cpp				\

OBJ		=	$(SRC:%.cpp=%.o)

CXXFLAGS=	-W -Wall -Wextra -Wshadow -std=c++11 -I include/ -I ../../include -fPIC

LDFLAGS	=	-shared

CXX	=		g++

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		clean fclean re
