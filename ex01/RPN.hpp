#ifndef CPP_RPN_HPP
#define CPP_RPN_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <exception>

class RPN
{
public:
	RPN();
	RPN(const RPN &src);
	~RPN();
	RPN &operator=(const RPN &src);
	int	process_operations(std::string operations);
	void	sub_stack();
	void	add_stack();
	void	div_stack();
	void	mult_stack();
	class IllegalCharSequenceException : public std::exception
	{
		public:
		const char * what() const throw();
	};
	class UnknownCharException : public std::exception
	{
	public:
		const char * what() const throw();
	};
	class DivisionByZeroException : public std::exception
	{
	public:
		const char * what() const throw();
	};
	class InsufficientContentException : public std::exception
	{
	public:
		const char * what() const throw();
	};
private:
	std::stack<int> _stack;
};


#endif //CPP_RPN_HPP
