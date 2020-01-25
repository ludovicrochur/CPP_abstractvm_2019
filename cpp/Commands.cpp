#include "../hpp/Commands.hpp"
#include "../hpp/Base.hpp"
#include "../hpp/Regex.hpp"
#include "../hpp/Exceptions.hpp"
#include <iomanip>

void	Commands::del_io(const IOperand ** obj)
{
	delete *obj;
	*obj = nullptr;
}

// --------------------------- Commands Without Value --------------------------
void	Commands::pop(Base & bs)
{
	if (bs.stack_.empty())
		throw Exceptions::EmptyStackError(bs.result_[REGEX_CMD_INDEX]);
	right_ = bs.stack_.back();
	bs.stack_.pop_back();
	del_io(&right_);
}

void	Commands::dump(Base & bs)
{
	for (auto i = bs.stack_.rbegin(); i != bs.stack_.rend(); ++i)
		std::cout << (*i)->toString() << std::endl;
}

void	Commands::add(Base & bs)
{
	if (bs.stack_.size() < CE_MINIMUM_ARGS)
		throw Exceptions::NotEnoughArgumentsError();
	right_ = bs.stack_.back();
	bs.stack_.pop_back();
	left_ = bs.stack_.back();
	bs.stack_.pop_back();
	const IOperand *res = *left_ + *right_;
	bs.stack_.push_back(res);
	del_io(&left_);
	del_io(&right_);
}

void	Commands::sub(Base & bs)
{
	if (bs.stack_.size() < CE_MINIMUM_ARGS)
		throw Exceptions::NotEnoughArgumentsError();
	right_ = bs.stack_.back();
	bs.stack_.pop_back();
	left_ = bs.stack_.back();
	bs.stack_.pop_back();
	const IOperand *res = *left_ - *right_;
	bs.stack_.push_back(res);
	del_io(&left_);
	del_io(&right_);
}

void	Commands::mul(Base & bs)
{
	if (bs.stack_.size() < CE_MINIMUM_ARGS)
		throw Exceptions::NotEnoughArgumentsError();
	right_ = bs.stack_.back();
	bs.stack_.pop_back();
	left_ = bs.stack_.back();
	bs.stack_.pop_back();
	const IOperand *res = *left_ * *right_;
	bs.stack_.push_back(res);
	del_io(&left_);
	del_io(&right_);
}

void	Commands::div(Base & bs)
{
	if (bs.stack_.size() < CE_MINIMUM_ARGS)
		throw Exceptions::NotEnoughArgumentsError();
	right_ = bs.stack_.back();
	bs.stack_.pop_back();
	left_ = bs.stack_.back();
	bs.stack_.pop_back();
	const IOperand *res = *left_ / *right_;
	bs.stack_.push_back(res);
	del_io(&left_);
	del_io(&right_);
}

void	Commands::mod(Base & bs)
{
	if (bs.stack_.size() < CE_MINIMUM_ARGS)
		throw Exceptions::NotEnoughArgumentsError();
	right_ = bs.stack_.back();
	bs.stack_.pop_back();
	left_ = bs.stack_.back();
	bs.stack_.pop_back();
	const IOperand *res = *left_ % *right_;
	bs.stack_.push_back(res);
	del_io(&left_);
	del_io(&right_);
}

void	Commands::print(Base & bs)
{
	if (bs.stack_.empty())
		throw Exceptions::EmptyStackError(bs.result_[REGEX_CMD_INDEX]);
	right_ = bs.stack_.back();
	if (right_->getType() != Int8)
	{
		right_ = nullptr;
		throw Exceptions::PrintCommandError();
	}
	int8_t c = static_cast<int8_t>(std::stoi(right_->toString()));
	std::cout << c << std::endl;
	right_ = nullptr;
}

void	Commands::exit(Base & bs)
{
	bs.is_exit_command_ = false;
}


// -----------------------------------------------------------------------------
void	Commands::execute_command(Base & bs)
{
	(this->*cmd_[bs.result_[REGEX_CMD_INDEX]])(bs);
}

Commands	&Commands::operator=(Commands const & rhs)
{
	if (this != &rhs)
	{
		
	}
	return (*this);
}
Commands::Commands(Commands const & rhs) { *this = rhs; }
Commands::Commands(void)
{

	cmd_.emplace(CM_POP, &Commands::pop);
	cmd_.emplace(CM_DUMP, &Commands::dump);
	cmd_.emplace(CM_ADD, &Commands::add);
	cmd_.emplace(CM_SUB, &Commands::sub);
	cmd_.emplace(CM_MUL, &Commands::mul);
	cmd_.emplace(CM_DIV, &Commands::div);
	cmd_.emplace(CM_MOD, &Commands::mod);
	cmd_.emplace(CM_PRINT, &Commands::print);
	cmd_.emplace(CM_EXIT, &Commands::exit);


	left_ = nullptr;
	right_ = nullptr;
}
Commands::~Commands(void)
{
	del_io(&left_);
	del_io(&right_);
}
