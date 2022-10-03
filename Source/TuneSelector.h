#pragma once
#include<map>
#include<JuceHeader.h>


#include"GuitarTunes.h"


class TuneSelector :
	public juce::Component,
	public juce::ComboBox::Listener,
	public GuitarTunes::Listener
{
public:
	TuneSelector();
	virtual ~TuneSelector() = default;

	void paint(juce::Graphics&) override;
	void resized() override;

	void comboBoxChanged(juce::ComboBox*) override;

	void onEvent(GuitarTunes::TuneAdded) override;
	void onEvent(GuitarTunes::TuneIsChanged) override;

	GuitarTunes* getGuitarTunes();

private:
	juce::ComboBox	m_combobox;
	GuitarTunes		m_guitar_tunes;
	uint32_t		m_tune_counter{ 1 };

	std::map<std::string, int>	m_tune_ids;
};