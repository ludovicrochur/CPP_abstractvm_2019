NAME		=	abstractVM
FLAGS		= 	-Wall -Werror -Wextra
COMPILER	=	g++ -std=c++11

DIR_HPP		=	./hpp/
DIR_CPP		=	./cpp/
DIR_OBJ		= 	./obj/

#-------------------------- Header files ---------------------------------------
HEAD_AVM	=	IOperand.hpp\
				Exceptions..hpp\
				Base.hpp\
				Regex.hpp\
				Factory.hpp\
				Operand.hpp\
				Commands.hpp\
				Casts..hpp

#-------------------------- Source files ---------------------------------------
CPP_AVM		=	main.cpp\
				Exceptions.cpp\
				Base.cpp\
				Factory.cpp\
				Commands.cpp

HPP_PATH 	= 	$(addprefix $(DIR_HPP), $(HEAD_AVM))

OBJ 		= 	$(addprefix $(DIR_OBJ), $(CPP_AVM:.cpp=.o))
HPP 		= 	$(addprefix -I, $(DIR_HPP))

all: obj $(NAME)

obj:
	@mkdir -p $(DIR_OBJ)

#-------------------------- Compil Block ---------------------------------------
$(NAME): $(OBJ)
	@$(COMPILER) -o $(NAME) $(OBJ)

#-------------------------- Link Block -----------------------------------------
#source
$(DIR_OBJ)%.o: $(DIR_CPP)%.cpp $(HPP_PATH)
	@$(COMPILER) $(FLAGS) $(HPP) -c -o $@ $<

clean:
	@rm -rf $(DIR_OBJ)

fclean:
	@rm -rf $(DIR_OBJ)
	@rm -f $(NAME)

re: fclean all
