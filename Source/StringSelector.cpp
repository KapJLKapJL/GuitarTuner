#include "StringSelector.h"

#include<limits>

#include "Constants.h"

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

	// proportions
	constexpr float button_stride = 2.5 / 14.5;
	constexpr float button_width = 2. / 14.5;

	auto bounds = getLocalBounds();
	for (auto& button : m_string_buttons)
	{
		button.setBounds(
			bounds.getWidth() * string_index * button_stride,
			bounds.getY(),
			bounds.getWidth() * button_width,
			bounds.getHeight()
		);

		string_index--;
	}
}

void StringSelector::onEvent(GuitarTunes::TuneIsChanged)
{
	auto tune = m_tunes->getCurrentTune();
	for (int i = 0; i < 6; ++i)
	{
		m_string_buttons[i].setColour(juce::TextButton::buttonOnColourId, tunerConstants::selected_color);
		m_string_buttons[i].setColour(juce::TextButton::buttonColourId, tunerConstants::default_color);
		m_string_buttons[i].setButtonText(tune.getStringName(i));
	}
}

void StringSelector::onEvent(StringsModel::IsTuned)
{
	auto id = m_model.getCurrentStringId();
	m_string_buttons[id].setColour(juce::TextButton::buttonOnColourId, tunerConstants::tuned_color);
	m_string_buttons[id].setColour(juce::TextButton::buttonColourId, tunerConstants::tuned_color);
}

void StringSelector::onEvent(StringsModel::FreqChange)
{
	m_string_buttons[m_model.getCurrentStringId()].triggerClick();
}

float StringSelector::getStringFrequency()
{
	auto tune = m_tunes->getCurrentTune();
	auto id = m_model.getCurrentStringId();
	return tune.getStringFreq(id);
}

int StringSelector::getNearestString(float freq)
{
	auto tune = m_tunes->getCurrentTune();

	float min_diff = std::numeric_limits<float>::max();
	int idx_min = 0;
	for (int i = 0; i < 6; ++i)
	{
		auto note = tune.getNote(i);
		auto diff = note.calcFrequencyDifference(freq);
		if (min_diff > abs(diff))
		{
			min_diff = abs(diff);
			idx_min = i;
		}
	}

	return idx_min;
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
