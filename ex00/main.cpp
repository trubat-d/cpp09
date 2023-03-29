#include <fstream>
#include <iostream>
#include <ctime>
#include <sstream>
#include <map>
#define DATABASES_FILE "data.csv"

struct compare_tm
{
	bool operator()(const std::tm &a, const std::tm &b) const
	{
		std::time_t	ta = std::mktime(const_cast<tm *>(&a));
		std::time_t tb = std::mktime(const_cast<tm *>(&b));
		return (ta < tb);
	}
};

void	read_database(std::map<std::tm, float, compare_tm> &data)
{
	float 								value;
	std::tm								t = {};
	std::string 						line;
	std::ifstream						file;

	file.open(DATABASES_FILE);
	if (file.bad())
		throw std::runtime_error("to open databases");
	getline(file, line);
	while (getline(file, line))
	{
		char 				c;
		std::istringstream	flux(line);
		//https://en.cppreference.com/w/cpp/chrono/c/tm
		flux >> t.tm_year >> c >> t.tm_mon >> c >> t.tm_mday >> c >> value;
		t.tm_mon -= 1;
		if (mktime(&t) == -1)
			throw std::runtime_error("wrong time in database");
		data.insert(std::pair<std::tm const, float>(t, value));;
	}
	file.close();
}

float	find_date(std::map<std::tm, float, compare_tm> &data, std::tm t)
{
	std::map<std::tm, float, compare_tm>::iterator	iter;
	const std::time_t								one_day = 24 * 60 * 60;
	std::time_t										tmp_value;
	std::time_t										begin_date;

	tmp_value = mktime(&t);
	begin_date = mktime(const_cast<std::tm *>(&(data.begin()->first)));
	while ((iter = data.find(t)) == data.end() && begin_date <= tmp_value)
	{
		tmp_value = mktime(&t) - one_day;
		t = *localtime(&tmp_value);
	}
	if (begin_date > tmp_value)
		return (-1);
	return (iter->second);
}

void test_case(std::map<std::tm, float, compare_tm> &data, const std::string& file_name)
{
	float 				value;
	std::string 		line;
	std::ifstream		file;
	std::tm				t = {};

	file.open(file_name);
	if (file.bad())
		throw std::runtime_error("cannot open input file");
	getline(file, line);
	while (getline(file, line))
	{
		char							 				c;
		std::istringstream								flux(line);

		flux >> t.tm_year >> c >> t.tm_mon >> c >> t.tm_mday >> c >> value;
		if (flux.fail())
			std::cout << "Error: bad input => " << line << std::endl;
		t.tm_mon -= 1;
		if (value < 0)
			std::cout << "Error: not a positive number." << std::endl;
		else if (mktime(&t) == -1)
			std::cout << "Error: bad input => " << line << std::endl;
		else if (value > 1000)
			std::cout << "Error: too large number" << std::endl;
		else
		{
			float 	price;
			c = '-';
			if ((price = find_date(data, t)) < 0)
				std::cout << "Error: not in database" << std::endl;
			else
				std::cout << t.tm_year << c << (t.tm_mon + 1) << c << t.tm_mday << " => " << value << " = " << (value * price) << std::endl;
		}
	}
}

int	main(int argc, char **argv)
{
	std::map<std::tm, float, compare_tm>	data;

	try
	{
		if (argc != 2)
			throw std::runtime_error("not enough arguments");
		read_database(data);
		test_case(data, std::string(argv[1]));
	}
	catch(std::runtime_error const &e)
	{
		std::cerr << "[FAILED]\t" << e.what() << std::endl;
	}
	catch(std::exception const &e)
	{
		std::cerr << "[EXCEPTION]\t" <<  e.what() << std::endl;
	}
	return (0);
}
