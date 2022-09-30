#pragma once

class IFreqFinder
{
public:
	virtual ~IFreqFinder() = default;

	virtual float calculate() = 0;
};