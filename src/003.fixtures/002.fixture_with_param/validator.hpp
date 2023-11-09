#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP

class Validator
{
private:
	int _min;
	int _max;
public:
	Validator(int min, int max);
	bool in_range(int value);
};

#endif
