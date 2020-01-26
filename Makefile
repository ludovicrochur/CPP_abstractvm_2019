NAME		=	abstractVM
FLAGS		= 	-Wall -Werror -Wextra
COMPILER	=	g++ -std=c++11

DIR_INC		=	./includes/
DIR_SRC		=	./source/
DIR_OBJ		= 	./obj/

#-------------------------- Header files ---------------------------------------
HEAD_AVM	=	IOperand.hpp\
				Exceptions.hpp\
				Base.hpp\
				Regex.hpp\
				Factory.hpp\
				Operand.hpp\
				Commands.hpp\
				Casts.hpp

#-------------------------- Source files ---------------------------------------
SRC_AVM		=	main.cpp\
				Exceptions.cpp\
				Base.cpp\
				Factory.cpp\
				Commands.cpp

INC_PATH 	= 	$(addprefix $(DIR_INC), $(HEAD_AVM))

OBJ 		= 	$(addprefix $(DIR_OBJ), $(SRC_AVM:.cpp=.o))
INC 		= 	$(addprefix -I, $(DIR_INC))

all: obj $(NAME)

obj:
	@mkdir -p $(DIR_OBJ)

#-------------------------- Compil Block ---------------------------------------
$(NAME): $(OBJ)
	@$(COMPILER) -o $(NAME) $(OBJ)

#-------------------------- Link Block -----------------------------------------
#source
$(DIR_OBJ)%.o: $(DIR_SRC)%.cpp $(INC_PATH)
	@$(COMPILER) $(FLAGS) $(INC) -c -o $@ $<

clean:
	@rm -rf $(DIR_OBJ)

fclean:
	@rm -rf $(DIR_OBJ)
	@rm -f $(NAME)

re: fclean all
