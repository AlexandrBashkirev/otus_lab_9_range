#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

std::vector<std::string> split(const std::string &str, char d)
{
	std::vector<std::string> r;

	std::string::size_type start = 0;
	std::string::size_type stop = str.find_first_of(d);
	while (stop != std::string::npos)
	{
		r.push_back(str.substr(start, stop - start));

		start = stop + 1;
		stop = str.find_first_of(d, start);
	}

	r.push_back(str.substr(start));

	return r;
}

template<typename _InIt, typename Pr, typename Func, typename... Args>
void predicated_for_each(_InIt first, _InIt last, Func func, Pr pr)
{
	assert(last > first);

	for (; first != last; ++first)
	{
		if (pr(*first))
			func(*first);
	}
}