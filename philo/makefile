#compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

# Name of the library
NAME = philo

# Source files and object files
SRC = free.c init.c main.c \
			monitore.c routine.c routine1.c \
			threads.c time.c utilis.c
OBJ	= $(SRC:.c=.o)

# Header files
HEADER = philo.h

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