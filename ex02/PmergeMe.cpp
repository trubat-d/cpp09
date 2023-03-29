#include "PmergeMe.h"

PmergeMe::PmergeMe() : _k(0){}

PmergeMe::PmergeMe(int k) : _k(k){}

PmergeMe::~PmergeMe(){}

PmergeMe::PmergeMe(const PmergeMe &src) : _k(src._k){}

PmergeMe &PmergeMe::operator=(const PmergeMe &src){(void)src;return (*this);}

void PmergeMe::list_insert(std::list<int> & lst)
{
	if(lst.size() <= 1)
		return ;
	std::list<int>::iterator it = lst.begin();
	std::list<int>::iterator itn = std::next(it,1);
	std::list<int>::iterator ite = lst.end();
	while(itn != ite)
	{
		while(it != ite  && *it < *itn)
			it++;
		while(it != ite && *it == *itn)
			it++;
		if(it != ite && *it > *itn)
		{
			std::list<int>::iterator tmp = itn;
			int tmp_val = *itn;
			tmp++;
			lst.erase(itn);
			lst.insert(it, tmp_val);
			itn = tmp;
		}
		else
			itn++;
		it = lst.begin();
	}
}

void PmergeMe::list_sort(std::list<int> & lst, int st, int end)
{
	if(static_cast<int>(lst.size()) > this->_k)
	{
		int mid = lst.size()/2;
		std::list<int> first_half;
		first_half.splice(first_half.begin(), lst, lst.begin(), std::next(lst.begin(), mid));
		list_sort(first_half, st, mid);
		std::list<int> sec_half;
		sec_half.splice(sec_half.begin(), lst,  std::next(lst.begin(), mid+1), lst.end());
		list_sort(sec_half, mid+1, end);
		lst = list_merge(first_half, sec_half);
	}
	else
	{
		list_insert(lst);
	}
}

std::list<int> PmergeMe::list_merge(std::list<int> &ar_fir, std::list<int> &ar_sec)
{
	std::list<int> lst;
	std::list<int>::iterator it_f = ar_fir.begin();
	std::list<int>::iterator ite_f = ar_fir.end();
	std::list<int>::iterator it_s = ar_sec.begin();
	std::list<int>::iterator ite_s = ar_sec.end();

	while(it_f != ite_f || it_s != ite_s)
	{
		if(it_f == ite_f)
		{
			lst.push_back(*it_s);
			it_s++;
		}
		else if (it_s == ite_s)
		{
			lst.push_back(*it_f);
			it_f++;
		}
		else
		{
			if(*it_f <= *it_s)
			{
				lst.push_back(*it_f);
				it_f++;
			}
			else
			{
				lst.push_back(*it_s);
				it_s++;
			}
		}
	}

	return (lst);
}

void PmergeMe::vect_insert(std::vector<int> & lst)
{
	if(lst.size() <= 1)
		return ;
	std::vector<int>::iterator it = lst.begin();
	std::vector<int>::iterator itn = std::next(it,1);
	std::vector<int>::iterator ite = lst.end();
	while(itn != ite)
	{
		while(it != ite && *it < *itn)
			it++;
		while(it != ite && *it == *itn)
			it++;
		if(it != ite && *it > *itn)
		{
			std::vector<int>::iterator tmp = itn;
			int tmp_val = *itn;
			tmp++;
			lst.erase(itn);
			lst.insert(it, tmp_val);
			itn = tmp;
		}
		else
			itn++;
		it = lst.begin();
	}
}

void PmergeMe::vect_sort(std::vector<int> & lst, int st, int end)
{
	if(static_cast<int>(lst.size()) > this->_k)
	{
		int mid = lst.size()/2;
		std::vector<int> first_half(lst.begin(), std::next(lst.begin(), mid));
		vect_sort(first_half, st, mid);
		std::vector<int> sec_half(std::next(lst.begin(), mid), lst.end());
		vect_sort(sec_half, mid, end);
		lst = vect_merge(first_half, sec_half);
	}
	else
	{
		vect_insert(lst);
	}
}

std::vector<int> PmergeMe::vect_merge(std::vector<int> &ar_fir, std::vector<int> &ar_sec)
{
	std::vector<int> lst;
	std::vector<int>::iterator it_f = ar_fir.begin();
	std::vector<int>::iterator ite_f = ar_fir.end();
	std::vector<int>::iterator it_s = ar_sec.begin();
	std::vector<int>::iterator ite_s = ar_sec.end();

	while(it_f != ite_f || it_s != ite_s)
	{
		if(it_f == ite_f)
		{
			lst.push_back(*it_s);
			it_s++;
		}
		else if (it_s == ite_s)
		{
			lst.push_back(*it_f);
			it_f++;
		}
		else
		{
			if(*it_f <= *it_s)
			{
				lst.push_back(*it_f);
				it_f++;
			}
			else
			{
				lst.push_back(*it_s);
				it_s++;
			}
		}
	}

	return (lst);
}