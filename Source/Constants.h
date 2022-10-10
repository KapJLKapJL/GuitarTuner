#pragma once
#include <JuceHeader.h>

namespace tunerConstants
{
	static juce::Colour tuned_color = juce::Colours::mediumvioletred;
	static juce::Colour selected_color = juce::Colour::fromRGB(133, 211, 250);
	static juce::Colour default_color = juce::Colour::fromRGB(0, 52, 77);


	static constexpr float diff_Hz = 2.f;
	static constexpr float screen_Hz = 60.f;
}
