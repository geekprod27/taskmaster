NAME		=	taskmaster
SRC			=	
RM			=	rm -rf
SRC_PATH	=	./src/
OBJ_PATH	=	./obj/
INC_PATH	=	./includes/
OBJ_DIRS	=	${OBJ_PATH}
OBJ			=	${addprefix ${OBJ_PATH},${SRC:.cxx=.o}}
PROGRESS	=	🔁
CHECK		=	✅

all:${NAME}

clean:
	@echo -n "\e[2K\r- \33[36mCleaning objects\33[0m [${PROGRESS}]"
	@${RM} ${OBJ_PATH}
	@echo -n "\e[2K\r- \33[31mCleaning objects\33[0m [${CHECK}]\n"

fclean:clean
	@echo -n "\e[2K\r- \33[36mCleaning execution file\33[0m [${PROGRESS}]"
	@${RM} ${NAME}
	@echo -n "\e[2K\r- \33[31mCleaning execution file\33[0m [${CHECK}]\n"

re:fclean
	@make --no-print-directory all

${OBJ_PATH}%.o:${SRC_PATH}%.cxx
	@echo -n "\e[2K\r- \33[1;34m$<\33[0m [${PROGRESS}]"
	@clang++  -c $< -o $@
	@echo -n "\e[2K\r- \33[1;32m$<\33[0m [${CHECK}]\n"

${OBJ_DIRS}:
	@mkdir ${OBJ_DIRS}

${NAME}:${OBJ_DIRS} ${OBJ}
	@echo -n "\e[2K\r- Build \33[1;33m${NAME}\33[0m [${PROGRESS}]"
	@gcc -O3 ${OBJ} -o ${NAME}
	@echo -n "\e[2K\r- Build \33[1;32m${NAME}\33[0m [${CHECK}]\n"


.PHONY:all clean fclean re