#compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

# Name of the library
NAME = philosopher

# Source files and object files
SRC = philo/free.c philo/init.c philo/main.c \
			philo/monitore.c philo/routine.c philo/routine1.c \
			philo/threads.c philo/time.c philo/utilis.c
OBJ	= $(SRC:.c=.o)

# Header files
HEADER = include/philo.h

all: $(NAME)

# Create philo
$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

# Compile object files
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

# Remove object files
clean:
	$(RM) $(OBJ)

# Remove object files and the library
fclean: clean
	$(RM) $(NAME)

# Rebuild the library
re: fclean all

# Phony targets
.PHONY: all clean fclean re