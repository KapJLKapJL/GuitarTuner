#include "StringsModel.h"

#include<algorithm>


StringsModel::StringsModel(Informator* informator) :
	m_informator(informator)
{
	m_strategi.reset(new ChangeStringOnButton(this));
}

void StringsModel::onEvent(IsTuned)
{
	std::for_each(m_listeners.begin(), m_listeners.end(),
		[](Listener* listener)
		{
			listener->onEvent(IsTuned());
		}
	);
}

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

int StringsModel::getCurrentStringId() const
{
	return m_current_string;
}

void StringsModel::ChangeStringOnFreqChange::onEvent(FreqChange event)
{
	auto new_string = m_model->getInformator()->getNearestString(event.freq);
	if (new_string != m_model->m_current_string)
	{
		m_model->m_current_string = new_string;
		for (auto& listener : m_model->m_listeners)
		{
			listener->onEvent(event);
		}
	}
}

void StringsModel::ChangeStringOnButton::onEvent(StringChange event)
{
	m_model->m_current_string = event.string;
}
