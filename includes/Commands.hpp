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

	void		ce_del_io(const IOperand ** obj);

	void	ce_pop(Base & bs);
	void	ce_dump(Base & bs);
	void	ce_add(Base & bs);
	void	ce_sub(Base & bs);
	void	ce_mul(Base & bs);
	void	ce_div(Base & bs);
	void	ce_mod(Base & bs);
	void	ce_print(Base & bs);
	void	ce_exit(Base & bs);

	void	ce_push(Base & bs);
	void	ce_assert(Base & bs);
public:
	void	ce_execute_command(Base & bs);

	Commands	&operator=(Commands const & rhs);
	Commands(Commands const & rhs);
	Commands(void);
	~Commands(void);
};

#endif
