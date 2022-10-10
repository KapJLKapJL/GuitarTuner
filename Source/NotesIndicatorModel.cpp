#include "NotesIndicatorModel.h"

void NotesIndicatorModel::onEvent(resetNote event)
{
	for (auto& listener : m_listeners)
	{
		listener->onEvent(event);
	}
}

void NotesIndicatorModel::addListener(Listener* listener)
{
	m_listeners.emplace_back(listener);
}

void NotesIndicatorModel::deleteListener(Listener* listener)
{
	auto listener_it = std::find(m_listeners.begin(), m_listeners.end(), listener);
	if (listener_it != m_listeners.end())
	{
		m_listeners.erase(listener_it);
	}
}
