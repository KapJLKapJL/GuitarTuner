#pragma once
#include<string>
#include<JuceHeader.h>

#include "NotesIndicatorModel.h"

class NoteIndicator :
	public juce::Component
{
public:
	virtual ~NoteIndicator() = default;

	void paint(juce::Graphics&) override;
	void resized() override;

	void setNoteName(std::string& note_name);

private:
	juce::String	m_note_name{ "" };
};

class NotesIndicator :
	public juce::Component,
	public NotesIndicatorModel::Listener
{
public:
	NotesIndicator();
	virtual ~NotesIndicator() = default;

	void paint(juce::Graphics&) override;
	void resized() override;

	void onEvent(NotesIndicatorModel::resetNote) override;

private:
	NoteIndicator	m_above_note;
	NoteIndicator	m_target_note;
	NoteIndicator	m_below_note;

	NotesIndicatorModel	m_model;
};