#include "FreqFinderNSDF.h"

#include<list>

float FreqFinderNSDF::calculate()
{
	auto min_iterator = std::min_element(m_NSDF.begin(), m_NSDF.end());
	auto max_iterator = std::max_element(m_NSDF.begin(), m_NSDF.end());
	auto max_difference = *max_iterator;

	std::list<int> max_indices;
	while (min_iterator != m_NSDF.end() || max_iterator != m_NSDF.end())
	{
		max_indices.emplace_back(std::distance(m_NSDF.begin(), m_NSDF.end()));
		min_iterator = std::min_element(max_iterator, m_NSDF.end());
		max_iterator = std::max_element(min_iterator, m_NSDF.end());
		if (min_iterator == max_iterator)
			break;
	}

	return *(max_indices.begin());
}
