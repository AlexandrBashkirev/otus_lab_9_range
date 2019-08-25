#define BOOST_TEST_MODULE test
#include <boost/test/unit_test.hpp>

#include <string>
#include <vector>
#include <algorithm>

#include <fstream>
#include <sstream>

#include "ip_worker.h"
#include "my_algorithm.h"

BOOST_AUTO_TEST_SUITE(range_test_suite)

BOOST_AUTO_TEST_CASE(test)
{
	// just for comfortable testing
	std::stringstream stream;
	std::vector<std::string> lines{ "1.70.44.170", "46.70.225.39", "222.173.235.246", "185.46.87.231" };

	for (auto line : lines)
		stream << line + '\n';

	std::vector<IP> ip_pool;

	for (std::string line; std::getline(stream, line);)
	{
		std::vector<std::string> v = split(line, '\t');
		ip_pool.push_back(parceIp(v.at(0), '.'));
	}

	// reverse lexicographically sort
	std::sort(ip_pool.begin(), ip_pool.end(), std::greater<IP>());

	BOOST_CHECK(ip_pool[0][0] == 222);

	predicated_for_each(ip_pool.begin(), ip_pool.end(), [](const IP& ip) {
		BOOST_CHECK(ip[0] == 1);
		}, IPFilter({ 1 }));

	predicated_for_each(ip_pool.begin(), ip_pool.end(), [](const IP& ip) {
		BOOST_CHECK(ip[1] == 70);
		}, IPFilter({ 46, 70 }));

	for (auto ip : ip_pool)
		if (filter_any(ip, 46))
			BOOST_CHECK(ip[0] == 46 || ip[1] == 46 || ip[2] == 46 || ip[3] == 46);
}

BOOST_AUTO_TEST_SUITE_END()