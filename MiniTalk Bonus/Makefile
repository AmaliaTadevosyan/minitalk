NAME1	= client
NAME2	= server
NAME3	= client_bonus
NAME4	= server_bonus
SRCS	= $(wildcard *.c)
OBJS	= $(patsubst %.c, %.o, $(SRCS))
CC		= gcc
FLAGS	= -Wall -Wextra -Werror
RM		= rm -f

%.o: %.c
		$(CC) $(FLAGS) -c $< -o $@
		
all: $(NAME1) $(NAME2)

bonus: $(NAME3) $(NAME4)

NAME1: $(OBJS)
		$(CC) $(FLAGS) client.o -o $(NAME1)

NAME2: $(OBJS) 
		$(CC) $(FLAGS) server.o -o $(NAME2)

NAME3: $(OBJS)
		$(CC) $(FLAGS) client_bonus.o -o $(NAME3)

NAME4: $(OBJS)
		$(CC) $(FLAGS) server_bonus.o -o $(NAME4)

clean:
		$(RM) $(OBJS)

fclean:	clean
		$(RM) $(NAME1) $(NAME2) $(NAME3) $(NAME4)

re: fclean all bonus

.PHONY: all clean fclean re