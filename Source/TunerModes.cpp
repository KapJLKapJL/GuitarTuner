#include "TunerModes.h"

TunerModes::TunerModes()
{
	initAutoButton();
	initChromaticButton();

	m_auto_button.triggerClick();

	setSize(100, 20);
}

void TunerModes::paint(juce::Graphics&)
{
}

void TunerModes::resized()
{
	// 14 symbols
	auto bounds = getLocalBounds();

	auto auto_bounds = bounds;
	auto_bounds.setWidth(bounds.getWidth()*4/14);

	m_auto_button.setBounds(auto_bounds);

	auto chromatic_bounds = bounds;
	chromatic_bounds.setX(auto_bounds.getX() + auto_bounds.getWidth() + bounds.getWidth() / 14);
	chromatic_bounds.setWidth(bounds.getWidth() * 9 / 14);

	m_chromatic_button.setBounds(chromatic_bounds);
}

TunerModesModel* TunerModes::getModel()
{
	return &m_model;
}

void TunerModes::initAutoButton()
{
	m_auto_button.setButtonText("Auto");
	m_auto_button.setClickingTogglesState(true);
	m_auto_button.setColour(juce::TextButton::buttonColourId,
		juce::Colour::fromRGB(0, 52, 77));
	m_auto_button.setColour(juce::TextButton::buttonOnColourId,
		juce::Colour::fromRGB(0, 172, 255));

	m_auto_button.onClick = [this]
	{
		m_auto_button.getToggleState() ?
			m_model.onEvent(TunerModesModel::AutoOn()) :
			m_model.onEvent(TunerModesModel::AutoOff());
	};

	addAndMakeVisible(m_auto_button);
}

void TunerModes::initChromaticButton()
{
	m_chromatic_button.setButtonText("Chromatic");
	m_chromatic_button.setClickingTogglesState(true);
	m_chromatic_button.setColour(juce::TextButton::buttonColourId,
		juce::Colour::fromRGB(0, 52, 77));
	m_chromatic_button.setColour(juce::TextButton::buttonOnColourId,
		juce::Colour::fromRGB(0, 172, 255));

	m_chromatic_button.onClick = [this]
	{
		m_chromatic_button.getToggleState() ?
			m_model.onEvent(TunerModesModel::ChromaticOn()) :
			m_model.onEvent(TunerModesModel::ChromaticOff());
	};

	addAndMakeVisible(m_chromatic_button);
}
