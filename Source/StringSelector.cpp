#include "StringSelector.h"

StringSelector::StringSelector(GuitarTunes* tunes) :
	m_tunes(tunes)
{
	tunes->addListener(this);
	m_model.addListener(this);

	makeButtons();
}

void StringSelector::onEvent(GuitarTunes::TuneIsChanged)
{
	auto tune = m_tunes->getCurrentTune();
	for (int i = 0; i < 6; ++i)
	{
		m_string_buttons[i].setColour(juce::TextButton::buttonOnColourId, juce::Colour::fromRGB(133, 211, 250));
		m_string_buttons[i].setColour(juce::TextButton::buttonColourId, juce::Colour::fromRGB(0, 52, 77));
		m_string_buttons[i].setButtonText(tune.getStringName(i));
	}
}

void StringSelector::onEvent(StringsModel::IsTuned)
{
	auto id = m_model.getCurrentStringId();
	m_string_buttons[id].setColour(juce::TextButton::buttonOnColourId, juce::Colour::fromRGB(0, 172, 255));
	m_string_buttons[id].setColour(juce::TextButton::buttonColourId, juce::Colour::fromRGB(0, 172, 255));
}

float StringSelector::getStringFrequency()
{
	auto tune = m_tunes->getCurrentTune();
	auto id = m_model.getCurrentStringId();
	return tune.getStringFreq(id);
}

int StringSelector::getNearestString(float freq)
{
	/*
	* 
	*/
	return 0;
}

void StringSelector::updateToggleState(juce::Button* button)
{
	int id = 0;
	for (; button != &m_string_buttons[id]; ++id);

	m_model.onEvent(StringsModel::StringChange{id});
}

void StringSelector::makeButtons()
{
	auto random = juce::Random::getSystemRandom().nextInt();
	for (auto& button : m_string_buttons)
	{
		addAndMakeVisible(button);
		button.setRadioGroupId(random);
	}

	m_string_buttons[0].onClick = [this] { updateToggleState(&m_string_buttons[0]); };
	m_string_buttons[1].onClick = [this] { updateToggleState(&m_string_buttons[1]); };
	m_string_buttons[2].onClick = [this] { updateToggleState(&m_string_buttons[2]); };
	m_string_buttons[3].onClick = [this] { updateToggleState(&m_string_buttons[3]); };
	m_string_buttons[4].onClick = [this] { updateToggleState(&m_string_buttons[4]); };
	m_string_buttons[5].onClick = [this] { updateToggleState(&m_string_buttons[5]); };

	m_string_buttons[0].setClickingTogglesState(true);
	m_string_buttons[1].setClickingTogglesState(true);
	m_string_buttons[2].setClickingTogglesState(true);
	m_string_buttons[3].setClickingTogglesState(true);
	m_string_buttons[4].setClickingTogglesState(true);
	m_string_buttons[5].setClickingTogglesState(true);

	setSize(100, 20);
}
