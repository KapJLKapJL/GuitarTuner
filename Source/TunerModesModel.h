#pragma once
#include<list>

class TunerModesModel
{
public:
	TunerModesModel() = default;
	~TunerModesModel() = default;

	struct AutoOn{};
	struct AutoOff {};
	struct ChromaticOn {};
	struct ChromaticOff {};
	class Listener
	{
	public:
		virtual ~Listener() = default;

		virtual void onEvent(AutoOn) {};
		virtual void onEvent(AutoOff) {};
		virtual void onEvent(ChromaticOn) {};
		virtual void onEvent(ChromaticOff) {};
	};
	void onEvent(AutoOn);
	void onEvent(AutoOff);
	void onEvent(ChromaticOn);
	void onEvent(ChromaticOff);

	void addListener(Listener*);
	void deleteListener(Listener*);

private:
	template <class Event>
	void notifyListeners(Event e)
	{
		for (auto& listener : m_listeners)
		{
			listener->onEvent(e);
		}
	}

	std::list<Listener*>	m_listeners;
};