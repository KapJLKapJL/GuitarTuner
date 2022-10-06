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
		virtual ~Listener() = default;

		virtual void onEvent(AutoOn) {};
		virtual void onEvent(AutoOff) {};
		virtual void onEvent(ChromaticOn) {};
		virtual void onEvent(ChromaticOff) {};
	};

	void addListener(Listener*);
	void deleteListener(Listener*);

private:
	std::list<Listener*>	m_listeners;
};