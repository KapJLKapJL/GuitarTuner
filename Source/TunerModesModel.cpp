#include "TunerModesModel.h"
#include<algorithm>

void TunerModesModel::onEvent(AutoOn e)
{
	notifyListeners(e);
}

void TunerModesModel::onEvent(AutoOff e)
{
	notifyListeners(e);
}

void TunerModesModel::onEvent(ChromaticOn e )
{
	notifyListeners(e);
}

void TunerModesModel::onEvent(ChromaticOff e)
{
	notifyListeners(e);
}

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
