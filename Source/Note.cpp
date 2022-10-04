#include "Note.h"

#include<array>
#include<optional>

class NotesContainer
{
public:
	std::string	getNote(int idx)
	{
		if (idx < 0)
			idx = 12 + idx;
		return m_notes[idx % 12];
	}
	std::optional<int>	getNoteIdx(std::string note_name)
	{
		for (int i = 11; i >= 0; --i) // sharp notes checked first
		{
			if (note_name.find(m_notes[i]) != std::string::npos)
			{
				return i;
			}
		}
		return std::nullopt;
	}
	std::optional<int>	getOctaveOfNote(std::string note_name)
	{
		auto idx = getNoteIdx(note_name);
		if (!idx)
			return std::nullopt;

		auto i = note_name.find(m_notes[idx.value()]);
		if (i != std::string::npos)
			note_name.erase(i, m_notes[idx.value()].length());

		return std::stoi(note_name);
	}

private:
	std::array<std::string, 12>	m_notes =
	{ "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
};


Note::Note(float frequency, float reference_frequency) :
	m_reference_frequency(reference_frequency)
{
	freqToNote(frequency);
}

Note::Note(std::string note_name_with_octave, float reference_frequency) :
	m_reference_frequency(reference_frequency)
{
	NotesContainer notes_container;
	auto note_opt = notes_container.getNoteIdx(note_name_with_octave);
	m_note_idx = note_opt.value_or(9);
	auto octave_opt = notes_container.getOctaveOfNote(note_name_with_octave);
	m_octave = octave_opt.value_or(4);
	noteToFrequency(m_note_idx, m_octave);
}

std::string Note::getNoteName()
{
	return NotesContainer().getNote(m_note_idx);
}

std::string Note::getNoteNameWithOctave()
{
	return getNoteName() + std::to_string(m_octave);
}

float Note::getFrequency()
{
	return m_frequency;
}

Note Note::getBelowNote()
{
	int note_idx = m_note_idx - 1;
	int octave = m_octave;
	if (note_idx < 0)
		octave -= 1;
	return Note(NotesContainer().getNote(note_idx) + std::to_string(octave));
}

Note Note::getAboveNote()
{
	int note_idx = m_note_idx + 1;
	int octave = m_octave;
	if (note_idx >= 12)
		octave += 1;
	return Note(NotesContainer().getNote(note_idx) + std::to_string(octave));
}

float Note::calcFrequencyDifference(float frequency)
{
	return 12 * 100 * log2(frequency/m_frequency);
}

void Note::freqToNote(float frequency)
{
	float C0 = m_reference_frequency * pow(2, -4.75);
	float note = round(12 * log2(frequency / C0));
	m_octave = note / 12;
	m_note_idx = static_cast<int>(note) % 12;
	
	noteToFrequency(m_note_idx, m_octave);
}

void Note::noteToFrequency(int note_idx, int octave)
{
	float C0 = m_reference_frequency * pow(2, -4.75);
	float h = note_idx + octave * 12.f;

	m_frequency = pow(2, h / 12.f) * C0;
}
