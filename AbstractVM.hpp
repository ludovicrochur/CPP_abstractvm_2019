#ifndef ABSTRACTVM_HPP
# define ABSTRACTVM_HPP
# include <list>
# include <map>
# include "IOperand.hpp"




class AbstractVM
{
	public:
		AbstractVM();
		AbstractVM(AbstractVM const & src);
		virtual ~AbstractVM();
		AbstractVM & operator=(AbstractVM const & rhs);
		std::list<const IOperand *> getStack() const;

		void push(eOperandType type, std::string const & value);
		void pop(eOperandType type, std::string const & value);
		void dump(eOperandType type, std::string const & value);
		void assert(eOperandType type, std::string const & value);
		void add(eOperandType type, std::string const & value);
		void sub(eOperandType type, std::string const & value);
		void mul(eOperandType type, std::string const & value);
		void div(eOperandType type, std::string const & value);
		void mod(eOperandType type, std::string const & value);
		void print(eOperandType type, std::string const & value);
		void exit(eOperandType type, std::string const & value);

		IOperand const * createOperand( eOperandType type, std::string const & value ) const;
		IOperand const * createInt8( std::string const & value ) const;
		IOperand const * createInt16( std::string const & value ) const;
		IOperand const * createInt32( std::string const & value ) const;
		IOperand const * createFloat( std::string const & value ) const;
		IOperand const * createDouble( std::string const & value ) const;

		void doInstruction(std::string const & instr, eOperandType type, std::string const & value);
		eOperandType getTypeWithString(std::string type);		
	private:
		std::list<const IOperand *>	_stack;
		IOperand const * (AbstractVM::*_tab[5]) (std::string const & value ) const;
		std::map<std::string, void (AbstractVM::*)(eOperandType type, std::string const & value) > _instruction;
};

#endif