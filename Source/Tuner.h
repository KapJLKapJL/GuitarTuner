#pragma once

#include "StringsModel.h"
#include "GuitarTunes.h"

class Tuner
{
public:
	Tuner(GuitarTunes*, StringsModel*);
	~Tuner() = default;

	void onEvent(StringsModel::FreqChange);
	void onEvent(StringsModel::AutoOn);
	void onEvent(StringsModel::AutoOff);
	void onEvent(StringsModel::IsTuned);

	double getFreqDifference() const;

private:
	GuitarTunes*	m_guitar_tunes;
	StringsModel*	m_string_model;

	double	m_freq_difference{ 100. }; // 100% = 1 tone
};