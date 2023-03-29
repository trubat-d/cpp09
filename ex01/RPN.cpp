#include "RPN.hpp"

RPN::RPN()
{

}

RPN::~RPN()
{

}

RPN::RPN(const RPN &src)
{
	this->_stack = src._stack;
}

RPN &RPN::operator=(const RPN &src)
{
	this->_stack = src._stack;
	return (*this);
}

void RPN::add_stack()
{
	if(this->_stack.size() < 2)
		throw InsufficientContentException();
	int first = this->_stack.top();
	this->_stack.pop();
	int sec = this->_stack.top();
	this->_stack.pop();
	this->_stack.push(sec + first);
}

void RPN::sub_stack()
{
	if(this->_stack.size() < 2)
		throw InsufficientContentException();
	int first = this->_stack.top();
	this->_stack.pop();
	int sec = this->_stack.top();
	this->_stack.pop();
	this->_stack.push(sec - first);
}

void RPN::div_stack()
{
	if(this->_stack.size() < 2)
		throw InsufficientContentException();
	int first = this->_stack.top();
	this->_stack.pop();
	int sec = this->_stack.top();
	this->_stack.pop();
	if(first == 0)
		throw DivisionByZeroException();
	this->_stack.push(sec / first);
}

void RPN::mult_stack()
{
	if(this->_stack.size() < 2)
		throw InsufficientContentException();
	int first = this->_stack.top();
	this->_stack.pop();
	int sec = this->_stack.top();
	this->_stack.pop();
	this->_stack.push(sec * first);
}


int RPN::process_operations(std::string operations)
{
	std::string::const_iterator it = operations.begin();
	std::string::const_iterator ite = operations.end();

	for(int sp = 1; it != ite; ++it)
	{
		if(isspace(*it))
			sp++;
		else if(*it == '-' || *it == '+' || *it == '/' || *it == '*')
		{
			if(sp == 0)
				throw IllegalCharSequenceException();
			switch (*it)
			{
				case '-':
					this->sub_stack();
					break;
				case '+':
					this->add_stack();
					break;
				case '/':
					this->div_stack();
					break;
				case '*':
					this->mult_stack();
					break;
			}
			sp = 0;
		}
		else if(isnumber(*it))
		{
			if(sp == 0)
				throw IllegalCharSequenceException();
			this->_stack.push(static_cast<int>(*it - '0'));
			sp = 0;
		}
		else
			throw UnknownCharException();
		if(sp > 1)
			throw IllegalCharSequenceException();
	}
	return this->_stack.top();
}

const char *RPN::IllegalCharSequenceException::what() const throw()
{
	return ("Number of Spaces needed between each characters : 1");
}

const char *RPN::UnknownCharException::what() const throw()
{
	return ("Illegal char found, operations are : *, /, -, +, every char separated by one space");
}

const char *RPN::DivisionByZeroException::what() const throw()
{
	return ("Trying to divide by zero !");
}

const char *RPN::InsufficientContentException::what() const throw()
{
	return ("The operation needs at least two values for operating");
}