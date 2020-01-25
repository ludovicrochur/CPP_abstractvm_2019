#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "Factory.hpp"
# include <iostream>
# include <string>
# include <map>

# define CE_MINIMUM_ARGS 2

class Base;

class Commands
{
private:
	std::map<std::string, eOperandType>								type_;
	std::map<std::string, void (Commands::*)(Base & bs)>	cmd_;

	const IOperand * right_;
	const IOperand * left_;

	void		del_io(const IOperand ** obj);

	void	pop(Base & bs);
	void	dump(Base & bs);
	void	add(Base & bs);
	void	sub(Base & bs);
	void	mul(Base & bs);
	void	div(Base & bs);
	void	mod(Base & bs);
	void	print(Base & bs);
	void	exit(Base & bs);
	
public:
	void	execute_command(Base & bs);

	Commands	&operator=(Commands const & rhs);
	Commands(Commands const & rhs);
	Commands(void);
	~Commands(void);
};

#endif
