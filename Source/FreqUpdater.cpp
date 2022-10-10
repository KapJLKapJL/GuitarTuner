#include "FreqUpdater.h"

#include "FreqFinderNSDF.h"
#include "Constants.h"

void FreqFinderGetter::setSampleRate(double sample_rate)
{
	m_sample_rate = sample_rate;
}

void FreqFinderGetter::pushSampleInRingBuffer(float sample)
{
	m_ring_buffer.push(sample);
}

std::unique_ptr<IFreqFinder> FreqFinderGetter::getFreqFinder()
{
	auto ptr = new FreqFinderNSDF(m_ring_buffer.begin(), m_ring_buffer.end(), m_sample_rate);
	return std::unique_ptr<IFreqFinder>(ptr);
}

FreqUpdater::FreqUpdater(FreqFinderGetter* freq_finder_getter, Tuner* tuner) :
	m_freq_finder_getter(freq_finder_getter),
	m_tuner(tuner)
{
	startTimerHz(tunerConstants::diff_Hz);
}

void FreqUpdater::timerCallback()
{
	auto freq_finder = m_freq_finder_getter->getFreqFinder();
	auto freq = freq_finder->calculate();
	if (freq)
	{
		float f_freq = freq.value();
		m_tuner->onEvent(StringsModel::FreqChange{ f_freq });
	}
}
