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

	auto bounds = getLocalBounds();
	g.setColour(juce::Colour::fromRGB(0, 52, 77));
	g.fillRoundedRectangle(bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight(), (bounds.getWidth() + bounds.getHeight()) / 32.f);

	juce::Rectangle<float>	indicator_bounds;
	indicator_bounds.setX(bounds.getWidth() * 0.05);
	indicator_bounds.setY(bounds.getHeight() * 0.05);
	indicator_bounds.setWidth(bounds.getWidth() * (1. - 0.05 * 2.));
	indicator_bounds.setHeight(bounds.getHeight() * (1. - 0.05 * 2.));

	float radius = indicator_bounds.getHeight();
	juce::Point<float> center{ indicator_bounds.getX() + indicator_bounds.getWidth() / 2.f, indicator_bounds.getY() + indicator_bounds.getHeight() };

	juce::Path indicator_back;
	//indicator_back.addArc(indicator_bounds.getX(), indicator_bounds.getY(), indicator_bounds.getWidth(), indicator_bounds.getHeight() * 2., -juce::float_Pi * 0.5, juce::float_Pi * 0.5, true);
	indicator_back.addCentredArc(center.x, center.y, radius, radius, 0.f, -juce::float_Pi * 0.5, juce::float_Pi * 0.5, true);
	indicator_back.closeSubPath();
	g.setColour(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
	g.fillPath(indicator_back);

	// draw measuring scale
	g.setColour(juce::Colours::white);
	for (int value = -150; value <= 150; value+=5)
	{
		auto rot_point = calcRotatedPoint(value);

		float scale_coef = 0.3;
		if (value == 0)
			scale_coef = 0.3;
		else if ((value % 10) == 0)
			scale_coef = 0.2;
		else if ((value % 5) == 0)
			scale_coef = 0.25;

		if (abs(value) > 110)
			scale_coef /= 2.f;

		juce::Line<float> line(
			center.x + rot_point.x * radius,
			center.y + rot_point.y * radius,
			center.x + rot_point.x * radius * (1.f - scale_coef),
			center.y + rot_point.y * radius * (1.f - scale_coef)
		);
		g.drawLine(line, 1.f - scale_coef);
	}

	auto difference = m_tuner->getFreqDifference();
	difference = m_transfer_function.update(difference);
	
	auto rot_point = calcRotatedPoint(difference);

	juce::Line<float> line(
		center.x,
		center.y,
		center.x + rot_point.x * radius,
		center.y + rot_point.y * radius
	);
	g.drawLine(line, 2.f);
}

void DifferenceIndicator::update()
{
}

void DifferenceIndicator::resized()
{
}

juce::Point<float> DifferenceIndicator::calcRotatedPoint(float value)
{
	juce::Point<float> point{ 1.f, 0.f };

	float diff_sign = value > 0 ? 1.f : -1.f;
	float visible_difference = 1. - exp(-(abs(value) * 0.02));
	visible_difference *= diff_sign;
	float angle = juce::float_Pi * (visible_difference * 0.5 + 0.5);
	float s = sin(angle);
	float c = cos(angle);

	juce::Point<float> rot_point;
	rot_point.setX(c * point.x + s * point.y);
	rot_point.setY(-s * point.x + c * point.y);
	return rot_point;
}
