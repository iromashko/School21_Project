# # В операционных системах GNU/Linux имена файлов библиотек должны иметь префикс "lib", статические библиотеки - расширение *.a, динамические - *.so.

# # NAME	=	s21_graph.a

# NAME_1	=	s21_graph.a

# SRC_1		=	main.cc s21_graph.cc

# HEADERS_1	=	s21_graph.h

# OBJS_1	=	${SRC_1:%.cpp=%.o}



# NAME_2	=	s21_graph_algorithms.a

# SRC_2		=	s21_graph_algorithms.cc

# HEADERS_2	=	s21_graph_algorithms.h

# OBJS_2	=	${SRC_2:%.cpp=%.o}

# FLAGS	=	-g -Wall -Werror -Wextra -lstdc++ -std=c++17 -Wno-unused

# CC		=	c++

# RM		=	rm -f

# .PHONY	:	all clean fclean re test

# # %.o		:	%.cpp ${HEADERS}
# # 	${CC} ${FLAGS} -c $< -o $@

# %.o		:	%.cpp ${HEADERS_1} ${HEADERS_2}
# 	${CC} ${FLAGS} -c $< -o $@

# ${NAME_1}:	${OBJS_1}
# 	${CC} ${FLAGS} -I ${HEADERS_1} ${SRC_1} -o $@

# # ${NAME}	:	${OBJS}
# # 	${CC} ${FLAGS} -I ${HEADERS} ${SRC} -o $@

# # all		:	${NAME}

# ${NAME_2}:	${OBJS_2}
# 	${CC} ${FLAGS} -I ${HEADERS_2} ${SRC_2} -o $@

# all		:	${NAME_1} ${NAME_2}

# clean	:
# 	${RM} ${OBJS}

# fclean	:	clean
# 	${RM} ${NAME}

# re		:	fclean all

# # test	:




all:	s21_graph_algorithms.h s21_graph.h s21_containers/s21_containers.h s21_containers/s21_stack.h s21_containers/s21_stack.tpp s21_containers/s21_utils.h
	c++ -g -Wall -Werror -Wextra -lstdc++ -std=c++17 -Wno-unused main.cpp s21_graph.cpp s21_containers/s21_utils.cpp s21_graph_algorithms.cpp -o graph
