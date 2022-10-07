#pragma once
#include <functional>

#include "StringsModel.h"
#include "GuitarTunes.h"
#include "TunerModesModel.h"

class Tuner :
	public TunerModesModel::Listener
{
public:
	Tuner(GuitarTunes*, StringsModel*, TunerModesModel*);
	~Tuner() = default;

	void onEvent(StringsModel::FreqChange);
	//void onEvent(StringsModel::AutoOn);
	//void onEvent(StringsModel::AutoOff);
	void onEvent(StringsModel::IsTuned);

	
	void onEvent(TunerModesModel::AutoOn) override;
	void onEvent(TunerModesModel::AutoOff) override;
	void onEvent(TunerModesModel::ChromaticOn) override;
	void onEvent(TunerModesModel::ChromaticOff) override;

	double getFreqDifference() const;

private:
	Note getStringNearestNote(float) const;
	Note getChromaticNearestNote(float) const;
	std::function<Note(float)>	getNoteStrategi;

	GuitarTunes*	m_guitar_tunes;
	StringsModel*	m_string_model;

	double	m_freq_difference{ 100. }; // 100% = 1 tone
};