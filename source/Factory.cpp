#include "../includes/Factory.hpp"
#include "../includes/Operand.hpp"
#include "../includes/Exceptions.hpp"
#include "../includes/Casts.hpp"

IOperand const	*Factory::Factory::createDouble(std::string const & value) const
{
	long double num = std::stold(value);

	if (num > DBL_MAX)
		throw Exceptions::OverflowError("double");
	else if (num < -DBL_MAX)
		throw Exceptions::UnderflowError("double");
	else
		return (new Operand<double>(SCD(num)));
}

IOperand const	*Factory::Factory::createFloat(std::string const & value) const
{
	long double num = std::stold(value);

	if (num > FLT_MAX)
		throw Exceptions::OverflowError("float");
	else if (num < -FLT_MAX)
		throw Exceptions::UnderflowError("float");
	else
		return (new Operand<float>(SCF(num)));
}

IOperand const	*Factory::Factory::createInt32(std::string const & value) const
{
	int64_t num = std::stoll(value);

	if (num > INT32_MAX)
		throw Exceptions::OverflowError("int32");
	else if (num < INT32_MIN)
		throw Exceptions::UnderflowError("int32");
	else
		return (new Operand<int32_t>(SC32(num)));
}

IOperand const	*Factory::Factory::createInt16(std::string const & value) const
{
	int64_t num = std::stoll(value);

	if (num > INT16_MAX)
		throw Exceptions::OverflowError("int16");
	else if (num < INT16_MIN)
		throw Exceptions::UnderflowError("int16");
	else
		return (new Operand<int16_t>(SC16(num)));
}

IOperand const	*Factory::Factory::createInt8(std::string const & value) const
{
	int64_t num = std::stoll(value);

	if (num > INT8_MAX)
		throw Exceptions::OverflowError("int8");
	else if (num < INT8_MIN)
		throw Exceptions::UnderflowError("int8");
	else
		return (new Operand<int8_t>(SC8(num)));
}

IOperand const	*Factory::Factory::createOperand(eOperandType type, std::string const & value) const
{
	return ((this->*func_[type])(value));
}

Factory::Factory	&Factory::Factory::operator=(Factory const & rhs)
{
	if (this != &rhs)
	{
		
	}
	return (*this);
}
Factory::Factory::Factory(Factory const & rhs) { *this = rhs; }
Factory::Factory::Factory(void)
{
	func_ = point_to_func_t(TYPE_SIZE);
	func_[Int8] = &Factory::createInt8;
	func_[Int16] = &Factory::createInt16;
	func_[Int32] = &Factory::createInt32;
	func_[Float] = &Factory::createFloat;
	func_[Double] = &Factory::createDouble;
}
Factory::Factory::~Factory(void) {}
