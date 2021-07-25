NAME		=	ft_containers

SRCS		=	srcs/maintest.cpp \
				srcs/test_map.cpp \
				srcs/test_node.cpp \
				srcs/test_vector.cpp \
				srcs/test_other.cpp \
				srcs/test_stack.cpp


OBJS		=	$(SRCS:.cpp=.o)
CC			=	clang++
FLAGS		=	-Wall -Wextra -Werror -std=c++98 -g
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

std:		fclean
			$(CC) $(FLAGS) $(INC_PATH) $(SRCS) -D NAMESPACE=std -o std_containers

test:		fclean
			$(CC) $(FLAGS) $(INC_PATH) $(SRCS) -D NAMESPACE=std -o test_std
			$(CC) $(FLAGS) $(INC_PATH) $(SRCS) -D NAMESPACE=ft -o test_fd
			./test_std > std.log
			./test_fd > fd.log
			rm -f test_std
			rm -f test_fd
			diff std.log fd.log

.PHONY:		clean fclean all re
