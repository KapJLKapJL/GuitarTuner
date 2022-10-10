#pragma once
#include<list>

#include "Note.h"

class NotesIndicatorModel
{
public:
	struct resetNote { Note note; };
	class Listener
	{
	public:
		virtual ~Listener() = default;

		virtual void onEvent(resetNote) {};
	};
	void onEvent(resetNote);

	void addListener(Listener*);
	void deleteListener(Listener*);

private:
	std::list<Listener*>	m_listeners;
};