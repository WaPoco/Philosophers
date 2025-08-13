#compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

# Name of the library
NAME = philosopher

# Source files and object files
SRC = src/free.c src/init.c src/main.c \
			src/monitore.c src/routine.c src/routine1.c \
			src/threads.c src/time.c src/utilis.c
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