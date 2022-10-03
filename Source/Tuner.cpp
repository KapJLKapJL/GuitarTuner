#include "Tuner.h"

Tuner::Tuner(GuitarTunes* guitar_tunes, StringsModel* string_model) :
	m_string_model(string_model),
	m_guitar_tunes(guitar_tunes)
{
    m_guitar_tunes->addTune(
        "E-standart",
        GuitarTune(
            "E", 329.6f,
            "B", 247.0f,
            "G", 196.0f,
            "D", 146.8f,
            "A", 110.0f,
            "E", 82.41f)
    );
    m_guitar_tunes->changeTune("E-standart");
    m_guitar_tunes->addTune(
        "Drop-D",
        GuitarTune(
            "E", 329.6f,
            "B", 247.0f,
            "G", 196.0f,
            "D", 146.8f,
            "A", 110.0f,
            "D", 73.43f)
    );

    onEvent(StringsModel::AutoOff());
}

void Tuner::onEvent(StringsModel::FreqChange event)
{
    m_string_model->onEvent(event);
}

void Tuner::onEvent(StringsModel::AutoOn event)
{
    m_string_model->onEvent(event);
}

void Tuner::onEvent(StringsModel::AutoOff event)
{
    m_string_model->onEvent(event);
}

void Tuner::onEvent(StringsModel::IsTuned event)
{
    m_string_model->onEvent(event);
}

double Tuner::getFreqDifference() const
{
    return m_freq_difference;
}