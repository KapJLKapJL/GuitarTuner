#include "FreqFinderNSDF.h"

std::optional<double> FreqFinderNSDF::calculate()
{
	auto max_idx_list = getMaxIndices();
	auto approximated_maximums = getApproximatedMaximums(std::move(max_idx_list));
	auto pitch = estimatePitchFromMaximums(std::move(approximated_maximums));

	return pitch;
}

std::list<int> FreqFinderNSDF::getMaxIndices() const
{
	std::list<int> max_indices;
	if (m_NSDF.empty())
		return max_indices;

	auto min_iterator = std::min_element(m_NSDF.begin(), m_NSDF.end());
	auto max_iterator = std::max_element(min_iterator, m_NSDF.end());
	auto max_difference = *max_iterator;

	while (min_iterator != m_NSDF.end() || max_iterator != m_NSDF.end())
	{
		max_indices.emplace_back(std::distance(m_NSDF.begin(), max_iterator));
		min_iterator = std::min_element(max_iterator, m_NSDF.end());
		max_iterator = std::max_element(min_iterator, m_NSDF.end());
		if (min_iterator == max_iterator)
			break;
	}

	return max_indices;
}

std::list<double> FreqFinderNSDF::getApproximatedMaximums(std::list<int>&& max_indices) const
{
	std::list<double> approximated_maximums;
	for (auto index : max_indices)
	{
		int x0_i = index;
		int x1_i = index + 1;
		int x2_i = index - 1;

		if (x2_i >= m_NSDF.size() || x1_i >= m_NSDF.size())
			continue;

		// idx to freq
		double x0 = m_sample_rate / x0_i;
		double x1 = m_sample_rate / x1_i;
		double x2 = m_sample_rate / x2_i;

		double y0 = m_NSDF[x0_i];
		double y1 = m_NSDF[x1_i];
		double y2 = m_NSDF[x2_i];

		double pitch = calcMaximumOfPorabola(x0, x1, x2, y0, y1, y2);
		double pitch_idx = m_sample_rate / pitch;

		approximated_maximums.emplace_back(pitch_idx);
	}

	return approximated_maximums;
}

std::optional<double> FreqFinderNSDF::estimatePitchFromMaximums(std::list<double>&& maximums) const
{
	if (maximums.empty())
		return std::nullopt;

	auto target_period = *maximums.begin();
	float prev_period = target_period;
	float sum_period = prev_period;
	int period_counter = 0;
	for (const auto& maximum_idx : maximums)
	{
		if (period_counter == 0)
		{
			period_counter = 1;
			continue;
		}

		auto period = maximum_idx - prev_period;
		prev_period = period;

		if (abs(period) > (abs(target_period) * 1.2f) || abs(period) < (abs(target_period) * 0.8f))
			continue;

		sum_period += period;
		period_counter++;
	}

	return m_sample_rate / (sum_period / period_counter);
}

double FreqFinderNSDF::calcMaximumOfPorabola(double x0, double x1, double x2, double y0, double y1, double y2) const
{
	/*
	y = a * x^2 + b * x + c
	y' = 2 * a * x + b

	x = - b / (2 * a)
	======================================

	system:
	a * x0 ^ 2 + b * x0 + c = y0
	a * x1 ^ 2 + b * x1 + c = y1
	a * x2 ^ 2 + b * x2 + c = y2

	A * X = B
	X = (a b c)
	B = (y0 y1 y2)
	A = (x0^2	x0	1
		 x1^2	x1	1
		 x2^2	x2	1)

	calculate a and b from this
	*/

	double a = (x1-x2)*y0+(-x0+x2)*y1+(x0-x1)*y2;
	double b = (-x1 * x1 + x2 * x2) * y0 + (x0*x0-x2*x2) * y1 + (-x0*x0+x1*x1) * y2;
	double x = -b / (2 * a);

	return x;
}
