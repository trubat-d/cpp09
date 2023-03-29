#include "PmergeMe.h"

int main(int ac, char **av)
{
	if(ac < 2)
	{
		std::cout << "Send at least a list of two positive integers" << std::endl;
		return (1);
	}
	std::list<int> lst;
	std::vector<int> vect;
	vect.reserve(ac+1);
	for(int i = 1; i < ac; i++)
	{
		int test = atoi(av[i]);
		if(test <= 0)
		{
			std::cout << "Only positive integers are allowed" << std::endl;
			return (1);
		}
		lst.push_back(test);
		vect.push_back(test);
	}
	PmergeMe merger(5);

	std::cout << "Before : ";
	for(std::list<int>::iterator it = lst.begin(), end=lst.end(); it != end; it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	const clock_t beginlist = std::clock();
	merger.list_sort(lst, 0, ac-1);
	double endlist = static_cast<double> (std::clock() - beginlist) / CLOCKS_PER_SEC;
	const clock_t beginvect = std::clock();
	merger.vect_sort(vect, 0, ac-1);
	double endvect = static_cast<double> (std::clock() - beginvect) / CLOCKS_PER_SEC;

	std::cout << "After : ";
	for(std::vector<int>::iterator it = vect.begin(), end=vect.end(); it != end; it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	std::cout << std::fixed << "Time to process a range of " << ac-1 << " elements with std::[list] : "  << endlist << "us" << std::endl;
	std::cout << std::fixed << "Time to process a range of " << ac-1 << " elements with std::[vector] : "  << endvect << "us" << std::endl;
}