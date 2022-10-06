#include "TunerModesModel.h"

void TunerModesModel::addListener(Listener* listener)
{
	m_listeners.emplace_back(listener);
}

void TunerModesModel::deleteListener(Listener* listener)
{
	auto listener_it = std::find(m_listeners.begin(), m_listeners.end(), listener);
	if (listener_it != m_listeners.end())
	{
		m_listeners.erase(listener_it);
	}
}
