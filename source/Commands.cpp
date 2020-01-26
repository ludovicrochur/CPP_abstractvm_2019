#include "../includes/Commands.hpp"
#include "../includes/Base.hpp"
#include "../includes/Regex.hpp"
#include "../includes/Exceptions.hpp"
#include <iomanip>

void	Commands::ce_del_io(const IOperand ** obj)
{
	delete *obj;
	*obj = nullptr;
}

void	Commands::ce_pop(Base & bs)
{
	if (bs.stack_.empty())
		throw Exceptions::EmptyStackError(bs.result_[REGEX_CMD_INDEX]);
	right_ = bs.stack_.back();
	bs.stack_.pop_back();
	ce_del_io(&right_);
}

void	Commands::ce_dump(Base & bs)
{
	for (auto i = bs.stack_.rbegin(); i != bs.stack_.rend(); ++i)
		std::cout << (*i)->toString() << std::endl;
}

void	Commands::ce_add(Base & bs)
{
	if (bs.stack_.size() < CE_MINIMUM_ARGS)
		throw Exceptions::NotEnoughArgumentsError();
	right_ = bs.stack_.back();
	bs.stack_.pop_back();
	left_ = bs.stack_.back();
	bs.stack_.pop_back();
	const IOperand *res = *left_ + *right_;
	bs.stack_.push_back(res);
	ce_del_io(&left_);
	ce_del_io(&right_);
}

void	Commands::ce_sub(Base & bs)
{
	if (bs.stack_.size() < CE_MINIMUM_ARGS)
		throw Exceptions::NotEnoughArgumentsError();
	right_ = bs.stack_.back();
	bs.stack_.pop_back();
	left_ = bs.stack_.back();
	bs.stack_.pop_back();
	const IOperand *res = *left_ - *right_;
	bs.stack_.push_back(res);
	ce_del_io(&left_);
	ce_del_io(&right_);
}

void	Commands::ce_mul(Base & bs)
{
	if (bs.stack_.size() < CE_MINIMUM_ARGS)
		throw Exceptions::NotEnoughArgumentsError();
	right_ = bs.stack_.back();
	bs.stack_.pop_back();
	left_ = bs.stack_.back();
	bs.stack_.pop_back();
	const IOperand *res = *left_ * *right_;
	bs.stack_.push_back(res);
	ce_del_io(&left_);
	ce_del_io(&right_);
}

void	Commands::ce_div(Base & bs)
{
	if (bs.stack_.size() < CE_MINIMUM_ARGS)
		throw Exceptions::NotEnoughArgumentsError();
	right_ = bs.stack_.back();
	bs.stack_.pop_back();
	left_ = bs.stack_.back();
	bs.stack_.pop_back();
	const IOperand *res = *left_ / *right_;
	bs.stack_.push_back(res);
	ce_del_io(&left_);
	ce_del_io(&right_);
}

void	Commands::ce_mod(Base & bs)
{
	if (bs.stack_.size() < CE_MINIMUM_ARGS)
		throw Exceptions::NotEnoughArgumentsError();
	right_ = bs.stack_.back();
	bs.stack_.pop_back();
	left_ = bs.stack_.back();
	bs.stack_.pop_back();
	const IOperand *res = *left_ % *right_;
	bs.stack_.push_back(res);
	ce_del_io(&left_);
	ce_del_io(&right_);
}

void	Commands::ce_print(Base & bs)
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

void	Commands::ce_exit(Base & bs)
{
	bs.is_exit_command_ = false;
}

void	Commands::ce_push(Base & bs)
{
	bs.stack_.push_back(
		fac_.createOperand(
			type_[bs.result_[REGEX_TYPE_INDEX]],
			bs.result_[REGEX_VALUE_INDEX]));
}

void	Commands::ce_assert(Base & bs)
{
	if (bs.stack_.empty())
		throw Exceptions::EmptyStackError(bs.result_[REGEX_CMD_INDEX]);
	right_ = fac_.createOperand(
		type_[bs.result_[REGEX_TYPE_INDEX]],
		bs.result_[REGEX_VALUE_INDEX]);
	left_ = bs.stack_.back();
	if (!(*right_ == *left_))
	{
		std::string left_str =  left_->toString();
		left_ = nullptr;
		throw Exceptions::AssertError(right_->toString(), left_str);
	}
	left_ = nullptr;
	ce_del_io(&right_);
}

void	Commands::ce_execute_command(Base & bs)
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
	type_.emplace(TP_INT8, Int8);
	type_.emplace(TP_INT16, Int16);
	type_.emplace(TP_INT32, Int32);
	type_.emplace(TP_FLOAT, Float);
	type_.emplace(TP_DOUBLE, Double);

	cmd_.emplace(CM_POP, &Commands::ce_pop);
	cmd_.emplace(CM_DUMP, &Commands::ce_dump);
	cmd_.emplace(CM_ADD, &Commands::ce_add);
	cmd_.emplace(CM_SUB, &Commands::ce_sub);
	cmd_.emplace(CM_MUL, &Commands::ce_mul);
	cmd_.emplace(CM_DIV, &Commands::ce_div);
	cmd_.emplace(CM_MOD, &Commands::ce_mod);
	cmd_.emplace(CM_PRINT, &Commands::ce_print);
	cmd_.emplace(CM_EXIT, &Commands::ce_exit);

	cmd_.emplace(CM_PUSH, &Commands::ce_push);
	cmd_.emplace(CM_ASSERT, &Commands::ce_assert);

	left_ = nullptr;
	right_ = nullptr;
}
Commands::~Commands(void)
{
	ce_del_io(&left_);
	ce_del_io(&right_);
}
