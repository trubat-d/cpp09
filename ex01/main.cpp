#include "RPN.hpp"

int main(int ac, char **av)
{
	if(ac == 2)
	{
		try
		{
			std::string str(av[1]);
			RPN oper;
			std::cout << "Calculated value is : " << oper.process_operations(str) << std::endl;
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	return (0);
}