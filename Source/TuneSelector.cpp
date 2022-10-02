#include "TuneSelector.h"

TuneSelector::TuneSelector() :
	m_guitar_tunes(this)
{
	m_combobox.addListener(this);
	addAndMakeVisible(m_combobox);

    m_guitar_tunes.addTune(
        "E-standart",
        GuitarTune(
            "E", 329.6f,
            "B", 247.0f,
            "G", 196.0f,
            "D", 146.8f,
            "A", 110.0f,
            "E", 82.41f)
    );

    m_guitar_tunes.addTune(
        "Drop-D",
        GuitarTune(
            "E", 329.6f,
            "B", 247.0f,
            "G", 196.0f,
            "D", 146.8f,
            "A", 110.0f,
            "D", 73.43f)
    );
    m_combobox.setSelectedId(1);
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
		auto selected_id = m_combobox.getSelectedItemIndex();
		auto tune_name = m_combobox.getItemText(selected_id);

		if(tune_name.toStdString()!=m_guitar_tunes.getCurrentTune())
			m_guitar_tunes.changeTune(tune_name.toStdString());
	}
}

void TuneSelector::onEvent(GuitarTunes::TuneAdded new_tune)
{
	m_combobox.addItem(TRANS(new_tune.tune_name), m_tune_counter++);
}
