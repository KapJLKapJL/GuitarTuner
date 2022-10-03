#pragma once
#include <array>

#include <JuceHeader.h>

#include "StringsModel.h"
#include "GuitarTunes.h"

class StringSelector :
	public juce::Component,
	public StringsModel::Listener,
	public GuitarTunes::Listener,
	public StringsModel::Informator
{
public:
	StringSelector(GuitarTunes*);
	virtual ~StringSelector() = default;

	void onEvent(GuitarTunes::TuneIsChanged) override;
	void onEvent(StringsModel::IsTuned) override;

	float getStringFrequency() override;
	int getNearestString(float freq) override;

	void updateToggleState(juce::Button* button);

private:
	void makeButtons();

	StringsModel m_model;
	GuitarTunes* m_tunes;

	std::array<juce::TextButton, 6> m_string_buttons;
};
