##
## EPITECH PROJECT, 2020
## arcade
## File description:
## arcade: lib/ncurses/Makefile
##

NAME 	=	../lib_arcade_NCURSES.so

SRC		=	src/Ncurses.cpp				\
			src/ANcurses.cpp			\
			../../src/AEntity.cpp		\
			../../src/Entity.cpp		\
			../../src/ArcadeUtils.cpp	\
			../../src/FileReader.cpp	\

OBJ		=	$(SRC:%.cpp=%.o)

CXXFLAGS=	-W -Wall -Wextra -Wshadow -std=c++11 -I include/ -I ../../include -fPIC

LDFLAGS	=	-shared -lncurses

CXX	=		g++

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		 clean fclean re
