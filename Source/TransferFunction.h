#pragma once

class TransferFunction
{
public:
	TransferFunction(float T0, float Tq);
	~TransferFunction() = default;

	float update(float x);

private:
	float k1;
	float k2;
	float yd{ 0. };
	float y{ 100. };
	float Tq;
};