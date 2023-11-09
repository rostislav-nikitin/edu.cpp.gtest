#include "validator.hpp"

Validator::Validator(int min, int max) : _min(min), _max(max)
{
}

bool Validator::in_range(int value)
{
	return value >= _min && value <= _max;
}
