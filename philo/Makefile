NAME = philo
SRC	= main.c parsing.c routine.c monitor.c init.c utils.c pars_utils1.c
OBJ	= $(SRC:.c=.o)
CC	= cc
CFLAGS	= -Wall -Wextra -Werror -pthread 
RM	= rm -f
all:		$(NAME)
$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	$(RM) $(OBJ)
fclean:		clean
	$(RM) $(NAME)
re:		fclean $(NAME)