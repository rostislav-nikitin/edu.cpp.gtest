#include <vector>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <cmath>

#include "lib.h"

namespace Lib
{
	bool positive(int x)
	{
		return x > 0;
	}

	int count_positives(std::vector<int> const &vec)
	{
		return std::count_if(vec.begin(), vec.end(), positive);
	}

	void to_upper_case(char in_str[])
	{
		for(unsigned int i = 0; i < strlen(in_str); ++i)
			in_str[i] = toupper(in_str[i]);

	}

	double sqrt(double x)
	{
		if(x < 0)
			throw std::runtime_error("Negative argument");
			//throw "Error";

		return ::sqrt(x);
	}
	
}
