#include "StringSelector.h"

StringSelector::StringSelector(GuitarTunes* tunes) :
	m_tunes(tunes),
	m_model(this)
{
	tunes->addListener(this);
	m_model.addListener(this);

	makeButtons();
}

void StringSelector::paint(juce::Graphics&)
{
}

void StringSelector::resized()
{
	int string_index = 5;
	auto bounds = getLocalBounds();
	auto button_width = bounds.getWidth() * (2.f + 2.f / 3.f) / 19.f;
	auto button_distance = bounds.getWidth() * 3.f / 19.f;
	auto button_x_offset = bounds.getWidth() * 2.f / (3.f * 19.f);
	auto button_height = bounds.getHeight() * 1.5f / 5.f;
	auto button_y_offset = bounds.getHeight() * 1.75f / 5.f;

	for (auto& button : m_string_buttons)
	{
		button.setBounds(
			button_x_offset + button_distance * string_index,
			button_y_offset,
			button_width,
			button_height
		);

		string_index--;
	}
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

StringsModel* StringSelector::getStringsModel()
{
	return &m_model;
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

	m_string_buttons[0].triggerClick();

	setSize(100, 20);
}
