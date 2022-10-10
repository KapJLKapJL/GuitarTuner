#include "NotesIndicator.h"
#include "Constants.h"

NotesIndicator::NotesIndicator()
{
	m_model.addListener(this);

	addAndMakeVisible(m_target_note);
	addAndMakeVisible(m_below_note);
	addAndMakeVisible(m_above_note);

	setSize(100, 20);
}

void NotesIndicator::paint(juce::Graphics& g)
{
}

void NotesIndicator::resized()
{
	auto bounds = getLocalBounds();

	auto below_note_bounds = bounds;
	below_note_bounds.setHeight(bounds.getHeight() * 0.5);
	below_note_bounds.setWidth(bounds.getWidth() * 1. / 8.);
	m_below_note.setBounds(below_note_bounds);

	auto target_note_bounds = bounds;
	target_note_bounds.setX(below_note_bounds.getWidth() + bounds.getWidth() * 2. / 8.);
	target_note_bounds.setWidth(bounds.getWidth() * 2. / 8.);
	m_target_note.setBounds(target_note_bounds);

	auto above_note_bounds = bounds;
	above_note_bounds.setHeight(bounds.getHeight() * 0.5);
	above_note_bounds.setX(target_note_bounds.getX() + target_note_bounds.getWidth() + bounds.getWidth() * 2. / 8);
	above_note_bounds.setWidth(below_note_bounds.getWidth());
	m_above_note.setBounds(above_note_bounds);
}

void NotesIndicator::onEvent(NotesIndicatorModel::resetNote event)
{
	auto target_note = event.note;
	auto below_note = target_note.getBelowNote();
	auto above_note = target_note.getAboveNote();

	m_target_note.setNoteName(target_note.getNoteNameWithOctave());
	m_below_note.setNoteName(below_note.getNoteName());
	m_above_note.setNoteName(above_note.getNoteName());

	repaint();
}

NotesIndicatorModel* NotesIndicator::getModelPtr()
{
	return &m_model;
}

void NoteIndicator::paint(juce::Graphics& g)
{
	auto bounds = getLocalBounds();
	g.setColour(tunerConstants::default_color);
	g.fillRoundedRectangle(bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight(), (bounds.getWidth() + bounds.getHeight()) / 8.f);

	g.setColour(juce::Colours::white);
	g.setFont(bounds.getHeight());
	g.drawText(m_note_name, bounds, juce::Justification::centred, 1);
}

void NoteIndicator::resized()
{
}

void NoteIndicator::setNoteName(std::string& note_name)
{
	m_note_name = juce::String(note_name);
}
