#include "StringsModel.h"

void StringsModel::onEvent(AutoOn)
{
	m_strategi.reset(new ChangeStringOnFreqChange(this));
}

void StringsModel::onEvent(AutoOff)
{
	m_strategi.reset(new ChangeStringOnButton(this));
}

float StringsModel::getStringFrequency()
{
	return m_informator->getStringFrequency();
}

StringsModel::Informator* StringsModel::getInformator()
{
	return m_informator;
}

void StringsModel::addListener(Listener* listener)
{
	m_listeners.emplace_back(listener);
}

void StringsModel::deleteListener(Listener* listener)
{
	auto listener_it = std::find(m_listeners.begin(), m_listeners.end(), listener);
	if (listener_it != m_listeners.end())
	{
		m_listeners.erase(listener_it);
	}
}

void StringsModel::onEvent(FreqChange event)
{
	m_strategi->onEvent(event);
}

void StringsModel::onEvent(StringChange event)
{
	m_strategi->onEvent(event);
}

void StringsModel::ChangeStringOnFreqChange::onEvent(FreqChange event)
{
	m_model->m_current_string = m_model->getInformator()->getNearestString(event.freq);
}

void StringsModel::ChangeStringOnButton::onEvent(StringChange event)
{
	m_model->m_current_string = event.string;
}
