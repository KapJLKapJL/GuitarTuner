#include "DifferenceIndicator.h"

DifferenceIndicator::DifferenceIndicator(Tuner* tuner) :
	m_tuner(tuner),
	m_transfer_function(1./(2.*3.14*2.5), 1./(2.*3.14*60.))
{
	setFramesPerSecond(60);
	setSize(100, 100);
}

void DifferenceIndicator::paint(juce::Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

	auto difference = m_tuner->getFreqDifference();
	difference = m_transfer_function.update(difference);
	float diff_sign = difference > 0 ? 1.f : -1.f;
	double visible_difference = 1. - exp(-(abs(difference) * 0.02));
	visible_difference *= diff_sign;

	auto bounds = getLocalBounds();
	auto center_X = static_cast<double>(bounds.getX()) + static_cast<double>(bounds.getWidth()) * 0.5;
	visible_difference *= static_cast<double>(bounds.getWidth()) * 0.5;

	juce::Line<float> line(
		center_X + visible_difference,
		static_cast<float>(bounds.getY()),
		center_X + visible_difference,
		static_cast<float>(bounds.getY()) + static_cast<float> (bounds.getWidth())
	);

	g.setColour(juce::Colour::fromRGB(255, 255, 255));
	g.drawLine(line, 2.);

	g.drawFittedText(juce::String(difference), getLocalBounds(), juce::Justification::centred, 1);
}

void DifferenceIndicator::update()
{
}

void DifferenceIndicator::resized()
{
}
