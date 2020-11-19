##
## EPITECH PROJECT, 2020
## arcade
## File description:
## arcade: lib/Makefile
##

all:
			@make -C Ncurses/ --no-print-directory
			@make -C SDL/ --no-print-directory
			@make -C SFML/ --no-print-directory

fclean:
			@make -C Ncurses/ fclean --no-print-directory
			@make -C SDL/ fclean --no-print-directory
			@make -C SFML/ fclean --no-print-directory

re	:	fclean all

.PHONY : clean fclean re
