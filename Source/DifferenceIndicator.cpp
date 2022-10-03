#include "DifferenceIndicator.h"

DifferenceIndicator::DifferenceIndicator(Tuner* tuner) :
	m_tuner(tuner)
{
	setFramesPerSecond(60);
	setSize(100, 100);
}

void DifferenceIndicator::paint(juce::Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

	g.drawFittedText(juce::String(m_tuner->getFreqDifference()), getLocalBounds(), juce::Justification::centred, 1);
}

void DifferenceIndicator::update()
{
}

void DifferenceIndicator::resized()
{
}
