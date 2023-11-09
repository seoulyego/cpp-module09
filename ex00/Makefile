NAME				:=	bitcoin_exchange
PROJECT_NAME		:=	BITCOIN_EXCHANGE

OBJ_DIR				:=	./.obj/
CACHE_DIR			:=	./.cache/

CC					:=	c++
CXXFLAGS			:=	-Wall -Wextra -Werror -std=c++98
MJFLAGS				 =	-MJ $@.part.json
RM					:=	rm -rf

SRC_FILES			:=	$(addsuffix .cpp,			\
							BitcoinExchange			\
							main					\
						)
OBJ_FILES			:=	$(SRC_FILES:.cpp=.o)
#JSON_FILES			:=	compile_commands.json

SRCS				:=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS				:=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))
OBJ_FOLDER			:=	$(OBJ_DIR)
PRINT				:=	$(PROJECT_NAME)

ifdef	DEBUG
		DBFLAGS		:=	-g -fsanitize=address
		PRINT		:=	$(addsuffix _DEBUG, $(PRINT))
endif

.PHONY	:	all
all		:	$(OBJ_FOLDER) $(NAME)

$(OBJ_FOLDER)	:
	@if [ ! -d $(OBJ_FOLDER) ]; then \
		mkdir -p $(OBJ_FOLDER); \
	fi

$(NAME)	:	$(OBJS)
	@$(CC) $(CXXFLAGS) $(DBFLAGS) -o $@ $^
	@echo "\033[01;32m         SUCCESS!        \033[0m"
#	@(printf [ && find . -name "*.part.json" | xargs cat && printf ]) > $(JSON_FILES);


$(OBJ_FOLDER)%.o	:	%.cpp
	@$(CC) $(CXXFLAGS) $(DBFLAGS) -c -o $@ $<
#	@$(CC) $(CXXFLAGS) $(DBFLAGS) $(MJFLAGS) -c -o $@ $<

.PHONY	:	debug
debug	:
	@make DEBUG=1 all

.PHONY	:	clean
clean	:
	@$(RM) $(OBJ_DIR) $(CACHE_DIR) $(JSON_FILES)
	@echo "\033[91m      REMOVE OBJECT      \033[0m"

.PHONY	:	fclean
fclean	:	clean
	@$(RM) $(NAME)
	@echo "\033[91m       FCLEAN DONE       \033[0m"

.PHONY	:	re
re		:	fclean
	@make all
