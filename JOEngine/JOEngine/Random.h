#ifndef _RANDOM_H_
#define _RANDOM_H_

#include "Math.h"

class Random
{
public:

	//Gives a random float between 0 and 1
	float FloatBinomial(const bool negative);

	//Gives a random integer between a and b included
	int	Int(const int a, const int b);

	//Gives a random integer between 0 and a
	//int Int(const int a)
	

private:
	LCG generator;
	
};


#endif _RANDOM_H_