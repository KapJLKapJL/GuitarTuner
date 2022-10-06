#pragma once
#include<JuceHeader.h>

#include"TunerModesModel.h"

class TunerModes :
	public juce::Component,
	public juce::Button::Listener
{
public:
	TunerModes();
	virtual ~TunerModes() = default;

	void paint(juce::Graphics&) override;
	void resized() override;

	TunerModesModel* getModel();

private:
	void initAutoButton();
	void initChromaticButton();

	juce::TextButton	m_auto_button;
	juce::TextButton	m_chromatic_button;

	TunerModesModel	m_model;
};
