#include "TransferFunction.h"

TransferFunction::TransferFunction(float T0, float Tq_) :
	Tq(Tq_)
{
	float eps = 0.4;
	k1 = 2. * eps * T0;
	k2 = T0 * T0;
}

float TransferFunction::update(float x)
{
	y = y + Tq * yd;
	yd = yd + Tq * (x - y - yd * k1) / k2;
	return y;
}
