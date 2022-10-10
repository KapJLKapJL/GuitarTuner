#include "Tuner.h"

#include "Note.h"

Tuner::Tuner(GuitarTunes* guitar_tunes, StringsModel* string_model, TunerModesModel* tuner_modes_model) :
	m_string_model(string_model),
	m_guitar_tunes(guitar_tunes)
{
    tuner_modes_model->addListener(this);

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

    onEvent(TunerModesModel::AutoOn());
}

void Tuner::onEvent(StringsModel::FreqChange event)
{
    m_string_model->onEvent(event);
    auto note = getNoteStrategi(event.freq);
    auto next_diff = note.calcFrequencyDifference(event.freq);
    if (abs(m_freq_difference) < 5.f && abs(next_diff) < 5.f)
        m_string_model->onEvent(StringsModel::IsTuned());
    m_freq_difference = next_diff;
}

/*
void Tuner::onEvent(StringsModel::AutoOn event)
{
    m_string_model->onEvent(event);
}

void Tuner::onEvent(StringsModel::AutoOff event)
{
    m_string_model->onEvent(event);
}
*/

void Tuner::onEvent(StringsModel::IsTuned event)
{
    m_string_model->onEvent(event);
}

void Tuner::onEvent(TunerModesModel::AutoOn)
{
    m_string_model->onEvent(StringsModel::AutoOn());
}

void Tuner::onEvent(TunerModesModel::AutoOff)
{
    m_string_model->onEvent(StringsModel::AutoOff());
}

void Tuner::onEvent(TunerModesModel::ChromaticOn)
{
    getNoteStrategi = [this](float f)
    {
        return getChromaticNearestNote(f);
    };
}

void Tuner::onEvent(TunerModesModel::ChromaticOff)
{
    getNoteStrategi = [this](float f)
    {
        return getStringNearestNote(f);
    };
}






double Tuner::getFreqDifference() const
{
    return m_freq_difference;
}

Note Tuner::getStringNearestNote(float) const
{
    auto string_freq = m_string_model->getStringFrequency();
    return Note(string_freq);
}

Note Tuner::getChromaticNearestNote(float f) const
{
    return Note(f);
}
