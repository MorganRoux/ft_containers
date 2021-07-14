NAME		=	ft_containers

SRCS		=	main.cpp

OBJS		=	$(SRCS:.cpp=.o)
CC			=	clang++
FLAGS		=	-Wall -Wextra -Werror -std=c++98
INC_PATH	=	-I./incs
COMPILE		=	$(CC) $(FLAGS) $(INC_PATH)

%.o : %.cpp
			$(CC) $(FLAGS) $(INC_PATH) -D NAMESPACE=ft -c $<  -o $(<:.cpp=.o)

all:		$(NAME)

$(NAME):	${OBJS}
			$(COMPILE) $(OBJS) -o $(NAME)

clean:
			rm -f ${OBJS}

fclean:
			rm -f ${OBJS}
			rm -f ${NAME}

re:			fclean all

test:		fclean
			$(CC) $(FLAGS) $(INC_PATH) $(SRCS) -D NAMESPACE=ft -o test_fd
			$(CC) $(FLAGS) $(INC_PATH) $(SRCS) -D NAMESPACE=std -o test_std
			./test_fd > fd.log
			./test_std > std.log
			rm -f test_fd
			rm -f test_std
			diff fd.log std.log

.PHONY:		clean fclean all re
