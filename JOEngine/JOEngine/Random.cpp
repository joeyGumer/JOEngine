#include "Random.h"




float Random::FloatBinomial(const bool negative = false)
{
	if (!negative)
		return generator.Float01Incl();
	else
		return generator.FloatNeg1_1();
}

int Random::Int(const int a, const int b)
{
	return a + (int)(	b * (double)generator.Int() / (generator.MaxInt() + 1.0));
}