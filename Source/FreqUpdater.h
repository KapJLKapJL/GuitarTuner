#pragma once
#include<memory>

#include<JuceHeader.h>

#include "RingBuffer.h"
#include "IFreqFinder.h"
#include "Tuner.h"

// ??????????????
class FreqFinderGetter
{
public:
	FreqFinderGetter() = default;
	virtual ~FreqFinderGetter() = default;

	void setSampleRate(double);

	void pushSampleInRingBuffer(float sample);

	std::unique_ptr<IFreqFinder> getFreqFinder();

private:
	static constexpr size_t ring_buffer_size = 2048;
	RingBuffer<float, ring_buffer_size>	m_ring_buffer;
	double	m_sample_rate;
};

class FreqUpdater :
	public juce::Timer
{
public:
	FreqUpdater(FreqFinderGetter*, Tuner*);
	virtual ~FreqUpdater() = default;

	void timerCallback() override;

private:
	FreqFinderGetter*	m_freq_finder_getter;
	Tuner*	m_tuner;
};