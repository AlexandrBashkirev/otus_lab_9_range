// range_main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <fstream>
#include <sstream>

#include "ip_worker.h"
#include "my_algorithm.h"

int main()
{
	try
	{
		std::vector<IP> ip_pool;

		// reading data
		for (std::string line; std::getline(std::cin, line);)
			ip_pool.push_back(parceIp(split(line, '\t').at(0), '.'));

		// reverse lexicographically sort
		std::sort(ip_pool.begin(), ip_pool.end(), std::greater<IP>());

		// print result
		std::for_each(ip_pool.begin(), ip_pool.end(), printIp);

		predicated_for_each(ip_pool.begin(), ip_pool.end(), printIp, IPFilter({ 1 }));

		predicated_for_each(ip_pool.begin(), ip_pool.end(), printIp, IPFilter({ 46, 70 }));

		for (auto ip : ip_pool)
			if (filter_any(ip, 46))
				printIp(ip);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}


