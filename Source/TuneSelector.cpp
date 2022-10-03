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
		auto selected_id = m_combobox.getSelectedItemIndex();
		auto tune_name = m_combobox.getItemText(selected_id);

		if(tune_name.toStdString()!=m_guitar_tunes.getCurrentTuneName())
			m_guitar_tunes.changeTune(tune_name.toStdString());
	}
}

void TuneSelector::onEvent(GuitarTunes::TuneAdded new_tune)
{
	m_combobox.addItem(TRANS(new_tune.tune_name), m_tune_counter);
    m_tune_ids.emplace(new_tune.tune_name, m_tune_counter++);
}

void TuneSelector::onEvent(GuitarTunes::TuneIsChanged tune)
{
    m_combobox.setSelectedId(m_tune_ids[tune.tune_name], juce::NotificationType::dontSendNotification);
}

GuitarTunes* TuneSelector::getGuitarTunes()
{
    return &m_guitar_tunes;
}
