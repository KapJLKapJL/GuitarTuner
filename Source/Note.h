#pragma once
#include<string>

class Note
{
public:
	Note(float frequency, float reference_frequency=440.f);
	Note(std::string note_name_with_octave, float reference_frequency = 440.f);

	std::string	getNoteName();
	std::string	getNoteNameWithOctave();
	float	getFrequency();

	Note	getBelowNote();
	Note	getAboveNote();

	float calcFrequencyDifference(float frequency);

protected:
	void	freqToNote(float frequency);
	void	noteToFrequency(int note_idx, int octave);

private:
	float	m_frequency{ 1.f };

	int	m_note_idx{ 0 };
	int m_octave{ 0 };

	float	m_reference_frequency;
};