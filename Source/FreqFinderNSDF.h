#pragma once
#include<vector>
#include<algorithm>
#include<iterator>
#include<list>
#include<optional>


#include "IFreqFinder.h"

/*
* Find pitch from Normalized sqare differrence function
* "A smarter way to find pitch", Philip McLeod, Geoff Wyvill, University of Otago
*/
class FreqFinderNSDF : IFreqFinder
{
public:
	template <class ItType>
	FreqFinderNSDF(ItType&& first, ItType&& last, double sample_rate) :
		m_sample_rate(sample_rate)
	{
		double x_t_quad = 0.;
		for (auto sample = first; sample != last; ++sample)
		{
			x_t_quad += (*sample) * (*sample);
		}

		auto size = std::distance(first, last);
		m_NSDF.resize(size);
		std::vector<double> buffer(size);
		auto it = first;
		for (size_t i = 0; i < size; i++)
		{
			buffer[i] = *it;
			++it;
		}

		m_NSDF[0] = 1.;
		for (int delta = 1; delta < size; ++delta)
		{
			double x_t_delta_quad = 0.;
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


	std::optional<double> calculate() override;

private:
	std::list<int>			getMaxIndices() const;
	std::list<double>		getApproximatedMaximums(std::list<int>&& max_indices) const;
	std::optional<double>	estimatePitchFromMaximums(std::list<double>&& maximums) const;

	double		calcMaximumOfPorabola(double x0, double x1, double x2,
									  double y0, double y1, double y2) const;

	std::vector<double> m_NSDF;
	double m_sample_rate;
};