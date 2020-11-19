##
## EPITECH PROJECT, 2020
## arcade
## File description:
## arcade: Makefile
##

NAME	=	arcade

NAME_TEST=	unit_tests

SRC_TEST=	tests/test_DirectoriesReader.cpp	\
			tests/test_Entity.cpp				\
			tests/test_Parser.cpp				\
			tests/test_ArcadeUtils.cpp			\
			tests/test_FileReader.cpp			\
			src/FileReader.cpp					\

SRC_MAIN=	src/main.cpp						\

SRC 	=	src/DLLoader.cpp					\
			src/DirectoriesReader.cpp			\
			src/Parser.cpp						\
			src/Core.cpp						\
			src/AEntity.cpp						\
			src/Entity.cpp						\
			src/Menu.cpp						\
			src/ArcadeException.cpp				\
			src/ArcadeUtils.cpp					\
			src/AGame.cpp						\

OBJ		=	$(SRC:%.cpp=%.o) $(SRC_MAIN:%.cpp=%.o)

OBJ_TEST=	$(SRC_TEST:%.cpp=%.o) $(SRC:%.cpp=%.o)

CXXFLAGS=	-W -Wall -Wextra -Wshadow -std=c++11 -I include/

CXX	=		g++

LDFLAGS	=	-ldl -Wl,-rpath=./

COV	=		$(SRC:%.cpp=%.gcda) $(SRC:%.cpp=%.gcno) $(SRC_TEST:%.cpp=%.gcda) $(SRC_TEST:%.cpp=%.gcno)

all:		games graphicals core

core:		$(OBJ)
			$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

games:
			@make -C games/ --no-print-directory

graphicals:
			@make -C lib/ --no-print-directory

clean:
			$(RM) $(OBJ) $(OBJ_TEST) $(COV)

fclean	:	clean
			$(RM) $(NAME) $(NAME_TEST)
			@make -C lib/ fclean --no-print-directory
			@make -C games/ fclean --no-print-directory

re	:	fclean all

tests_run: CXXFLAGS += -fprofile-arcs -ftest-coverage
tests_run: LDFLAGS += -lcriterion --coverage
tests_run:	$(OBJ_TEST)
				$(CXX) -o $(NAME_TEST) $(OBJ_TEST) $(LDFLAGS)
				@./$(NAME_TEST)
				gcovr --exclude tests

.PHONY : clean fclean re tests_run games graphicals
