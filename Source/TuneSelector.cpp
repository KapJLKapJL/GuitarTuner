#include "TuneSelector.h"

TuneSelector::TuneSelector() :
	m_guitar_tunes(this)
{
	m_combobox.addListener(this);
	addAndMakeVisible(m_combobox);
}

void TuneSelector::paint(juce::Graphics&)
{
}

void TuneSelector::resized()
{
	auto bounds = getLocalBounds();
	m_combobox.setBounds(bounds);
}

void TuneSelector::comboBoxChanged(juce::ComboBox* combobox)
{
	if (&m_combobox == combobox)
	{
		auto selected_id = m_combobox.getSelectedId();
		auto tune_name = m_combobox.getItemText(selected_id);

		m_guitar_tunes.changeTune(tune_name.toStdString());
	}
}

void TuneSelector::onEvent(GuitarTunes::TuneAdded new_tune)
{
	static uint32_t tune_counter = 0;
	m_combobox.addItem(TRANS(new_tune.tune_name), tune_counter++);
}
