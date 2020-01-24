#include "AbstractVM.hpp"
#include <iostream>
#include "Exception.hpp"
#include "Calculator.hpp"
#include "IOperand.hpp"
#include <math.h>
 
AbstractVM::AbstractVM()
{
	_tab[Int8] 	 = 	&AbstractVM::createInt8;
	_tab[Int16]  = 	&AbstractVM::createInt16;
	_tab[Int32]  = 	&AbstractVM::createInt32;
	_tab[Float]  = 	&AbstractVM::createFloat;
	_tab[Double] = 	&AbstractVM::createDouble;

	_instruction["push"]   = &AbstractVM::push;
	_instruction["pop"]    = &AbstractVM::pop;
	_instruction["dump"]   = &AbstractVM::dump;
	_instruction["assert"] = &AbstractVM::assert;
	_instruction["add"]    = &AbstractVM::add;
	_instruction["sub"]    = &AbstractVM::sub;
	_instruction["mul"]    = &AbstractVM::mul;
	_instruction["div"]    = &AbstractVM::div;
	_instruction["mod"]    = &AbstractVM::mod;
	_instruction["print"]  = &AbstractVM::print;
	_instruction["exit"]   = &AbstractVM::exit;
}


void AbstractVM::push(eOperandType type, std::string const & value)
{
	const IOperand *result = createOperand(type, value);
	_stack.push_front(result);
}

void AbstractVM::pop(eOperandType type, std::string const & value)
{
	(void)value;
	(void)type;
	if (_stack.empty())
		throw EMPTYSTACKException("Erreur pop sur une stack vide");
	_stack.erase(_stack.begin());
}

void AbstractVM::dump(eOperandType type, std::string const & value)
{
	(void)value;
	(void)type;
	std::list<const IOperand*>::iterator p = _stack.begin();
	while (p != _stack.end())
		std::cout << (*p++)->toString() << std::endl;
}

void AbstractVM::assert(eOperandType type, std::string const & value)
{
	std::list<const IOperand*>::iterator p = _stack.begin();

	if (type != (*p)->getType())
		throw DIFFERENTTYPEException("Erreur asset sur des types différents");
	if (stod(value) != stod((*p)->toString()))
		throw DIFFERENTVALUEException("Erreur asset sur des valeurs différentes");
}

void AbstractVM::add(eOperandType type, std::string const & value)
{
	(void)value;
	(void)type;
	std::list<const IOperand*>::iterator p = _stack.begin();
	IOperand const *result;

	if (_stack.size() < 2)
		throw EMPTYVALUESTACKException("Erreur operation sur une stack qui ne contient pas au moins 2 élements");
	result = **(++p) + **(--p);
	g_e.pop(Int8, "");
	g_e.pop(Int8, "");
	_stack.push_front(result);
}

void AbstractVM::sub(eOperandType type, std::string const & value)
{
	(void)value;
	(void)type;
	std::list<const IOperand*>::iterator p = _stack.begin();
	IOperand const *result;

	if (_stack.size() < 2)
		throw EMPTYVALUESTACKException("Erreur operation sur une stack qui ne contient pas au moins 2 élements");
	result = **(++p) - **(--p);
	g_e.pop(Int8, "");
	g_e.pop(Int8, "");
	_stack.push_front(result);
}

void AbstractVM::mul(eOperandType type, std::string const & value)
{
	(void)value;
	(void)type;
	std::list<const IOperand*>::iterator p = _stack.begin();
	IOperand const *result;

	if (_stack.size() < 2)
		throw EMPTYVALUESTACKException("Erreur operation sur une stack qui ne contient pas au moins 2 élements");
	result = **(++p) * **(--p);
	g_e.pop(Int8, "");
	g_e.pop(Int8, "");
	_stack.push_front(result);
}

void AbstractVM::div(eOperandType type, std::string const & value)
{
	(void)value;
	(void)type;
	std::list<const IOperand*>::iterator p = _stack.begin();
	IOperand const *result;

	if (_stack.size() < 2)
		throw EMPTYVALUESTACKException("Erreur operation sur une stack qui ne contient pas au moins 2 élements");
	result =  **(++p) / **(--p);
	g_e.pop(Int8, "");
	g_e.pop(Int8, "");
	_stack.push_front(result);
}

void AbstractVM::mod(eOperandType type, std::string const & value)
{
	(void)value;
	(void)type;
	std::list<const IOperand*>::iterator p = _stack.begin();
	IOperand const *result;

	if (_stack.size() < 2)
		throw EMPTYVALUESTACKException("Erreur operation sur une stack qui ne contient pas au moins 2 élements");
	result = **(++p) % **(--p);
	g_e.pop(Int8, "");
	g_e.pop(Int8, "");
	_stack.push_front(result);
}

void AbstractVM::print(eOperandType type, std::string const & value)
{
	(void)value;
	(void)type;
	if ((*_stack.begin())->getType())
		throw DIFFERENTTYPEException("Print type different de int8");
	printf("%c", std::stoi((*_stack.begin())->toString()));
}

void AbstractVM::exit(eOperandType type, std::string const & value)
{
	(void)value;
	(void)type;
	std::exit(0);
}

IOperand const * AbstractVM::createOperand( eOperandType type, std::string const & value ) const
{
	IOperand const *result = NULL;
	result = (this->*_tab[type])(value);
	return (result);
}

IOperand const * AbstractVM::createInt8( std::string const & value ) const
{
	double nb = stod(value);

	if (nb > 127)
		throw OVERFLOWException("Overflow int8");
	if (nb < -127)
		throw UNDERFLOWException("Underflow int8");
	return (new Calculator<char>((char)nb, Int8));
}

IOperand const * AbstractVM::createInt16( std::string const & value ) const
{
	double nb = stod(value);

	if (nb > 32767)
		throw OVERFLOWException("Overflow int16");
	if (nb < -32768)
		throw UNDERFLOWException("Underflow int16");
	return (new Calculator<short int>((short int)nb, Int16));
}

IOperand const * AbstractVM::createInt32( std::string const & value ) const
{
	double nb = stod(value);

	if (nb > 2147483647)
		throw OVERFLOWException("Overflow int32");
	if (nb < -2147483648)
		throw UNDERFLOWException("Underflow int32");
	return (new Calculator<long int>((long int)nb, Int32));
}

IOperand const * AbstractVM::createFloat( std::string const & value ) const
{
	double nb = stod(value);

	if (!isfinite(nb) && nb > 0)
		throw OVERFLOWException("Overflow float");
	if (!isfinite(nb) && nb < 0)
		throw UNDERFLOWException("Underflow float");
	return (new Calculator<float>((float)nb, Float));
}

IOperand const * AbstractVM::createDouble( std::string const & value ) const
{
	double nb = stod(value);

	if (!isfinite(nb) && nb > 0)
		throw OVERFLOWException("Overflow double");
	if (!isfinite(nb) && nb < 0)
		throw UNDERFLOWException("Underflow double");
	return (new Calculator<double>((double)nb, Double));
}

AbstractVM::~AbstractVM()
{

}

AbstractVM::AbstractVM(AbstractVM const & src)
{
	*this = src;
}

void AbstractVM::doInstruction(std::string const & instr, eOperandType type, std::string const & value)
{
	(this->*_instruction[instr])(type, value);
}

AbstractVM & AbstractVM::operator=(AbstractVM const & rhs)
{
	if (this != &rhs)
		this->_stack = rhs.getStack();
	return (*this);
}

std::list<const IOperand *> AbstractVM::getStack() const
{
	return (_stack);
}

eOperandType AbstractVM::getTypeWithString(std::string type)
{
	std::string names[5] = {"Int8", "Int16", "Int32", "Float", "Double"};
	
	if (!type.compare(names[0]))
		return (Int8);
	if (!type.compare(names[1]))
		return (Int16);
	if (!type.compare(names[2]))
		return (Int32);
	if (!type.compare(names[3]))
		return (Float);
	if (!type.compare(names[4]))
		return (Double);
	return (Int8);
}