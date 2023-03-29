#ifndef CPP_PMERGEME_H
#define CPP_PMERGEME_H

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <ctime>

class PmergeMe
{
public:
	PmergeMe();
	PmergeMe(int k);
	PmergeMe(const PmergeMe &src);
	~PmergeMe();
	PmergeMe &operator=(const PmergeMe &src);
	void	list_sort(std::list<int> &lst, int st, int end);
	std::list<int>	list_merge(std::list<int> &ar_fir, std::list<int> &ar_sec);
	void	list_insert(std::list<int> &lst);
	void	vect_sort(std::vector<int> &lst, int st, int end);
	std::vector<int>	vect_merge(std::vector<int> &ar_fir, std::vector<int> &ar_sec);
	void	vect_insert(std::vector<int> &lst);
private:
	const int _k;
};


#endif //CPP_PMERGEME_H
