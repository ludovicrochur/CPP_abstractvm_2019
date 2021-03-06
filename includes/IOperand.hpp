#ifndef IOPERAND_HPP
# define IOPERAND_HPP

# include <iostream>
# include <string>
# include <stdint.h>
# include <float.h>

enum	eOperandType {Int8, Int16, Int32, Float, Double, TYPE_SIZE};

class IOperand
{
public:
	virtual int getPrecision(void) const = 0; // Precision of the type of the instance
	virtual eOperandType getType(void) const = 0; // Type of the instance

	virtual IOperand const * operator+(IOperand const & rhs) const = 0; // Sum
	virtual IOperand const * operator-(IOperand const & rhs) const = 0; // Difference
	virtual IOperand const * operator*(IOperand const & rhs) const = 0; // Product
	virtual IOperand const * operator/(IOperand const & rhs) const = 0; // Quotient
	virtual IOperand const * operator%(IOperand const & rhs) const = 0; // Modulo

	virtual bool	operator==(IOperand const & rhs) const = 0; // Assert
	virtual bool	operator>(IOperand const & rhs) const = 0; // Bonus
	virtual bool	operator<(IOperand const & rhs) const = 0; // Bonus

	virtual std::string const & toString(void) const = 0; // String representation of the instance

	virtual ~IOperand(void) {}
};

#endif
