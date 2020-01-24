EXEC	= abstractVM

SRC		= main.cpp Exception.cpp AbstractVM.cpp

RM		= rm -f

FLAGS   = -Wall -Wextra -Werror

all:	$(EXEC) 

$(EXEC):
		g++ -o $(EXEC) $(SRC) $(FLAGS)

clean:
		$(RM) $(EXEC)

re:		clean all