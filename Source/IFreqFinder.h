#pragma once
#include<optional>

class IFreqFinder
{
public:
	virtual ~IFreqFinder() = default;

	virtual std::optional<double> calculate() = 0;
};