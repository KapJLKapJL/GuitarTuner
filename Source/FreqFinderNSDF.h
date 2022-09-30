#pragma once
#include<vector>
#include<algorithm>
#include<iterator>


#include "IFreqFinder.h"

/*
* Find pitch from Normalized sqare differrence function
* "A smarter way to find pitch", Philip McLeod, Geoff Wyvill, University of Otago
*/
class FreqFinderNSDF : IFreqFinder
{
public:
	template <class ItType>
	FreqFinderNSDF(ItType first, ItType last)
	{
		double x_t_quad = 0.;
		for (auto sample = first; sample != last; ++sample)
		{
			x_t_quad += sample * sample;
		}

		auto size = std::distance(first, last);
		m_NSDF.reserve(size);
		std::vector buffer(size);
		std::copy(first, last, std::back_inserter(buffer));

		for (int delta = 1; delta < size; ++delta)
		{
			double x_t_delta_squad = 0.;
			double ACF = 0.;

			for (int i = 0; i < (size - delta); i++)
			{
				x_t_delta_quad += buffer[i + delta] * buffer[i + delta];
				ACF += buffer[i] * buffer[i + delta];
			}
			m_NSDF[delta] = 2. * ACF / (x_t_quad + x_t_delta_quad);
		}
	}

	virtual ~FreqFinderNSDF() = default;


	float calculate() override;

private:
	std::vector<double> m_NSDF;
};