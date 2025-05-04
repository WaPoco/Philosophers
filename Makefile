Cc = cc
Cflags = -Wall -Wextra -Werror
Name = philo

Src = main.cc\
		...\


Objc = $(Src:.c=.o)
Header = philo.h

all: $(Name)

$(Name): $(Objc)
		ar rcs $(Name) $(Objc)

%.o: %.c $(Header)
	$(Cc) $(Cflags) -c $< -o $@

clean:
	rm -f $(Objc)

fclean: clean
	rm -f $(Name)

re: fclean all

.PHONY: all clean fclean re