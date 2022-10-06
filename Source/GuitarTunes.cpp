#include "GuitarTunes.h"

#include <algorithm>


GuitarTune::GuitarTune(std::string&& note1, float frequency1, std::string&& note2, float frequency2, std::string&& note3, float frequency3, std::string&& note4, float frequency4, std::string&& note5, float frequency5, std::string&& note6, float frequency6)
{
    setString(0, Note(frequency1));
    setString(1, Note(frequency2));
    setString(2, Note(frequency3));
    setString(3, Note(frequency4));
    setString(4, Note(frequency5));
    setString(5, Note(frequency6));
}

std::string GuitarTune::getStringName(int idx)
{
    return m_guitar_strings[idx].getNoteName();
}

float GuitarTune::getStringFreq(int idx)
{
    return m_guitar_strings[idx].getFrequency();
}

Note GuitarTune::getNote(int idx)
{
    return m_guitar_strings[idx];
}

void GuitarTune::setString(uint8_t idx, Note&& string_data)
{
    m_guitar_strings[idx] = std::move(string_data);
}

GuitarTunes::GuitarTunes(Listener* first)
{
    addListener(first);
}

void GuitarTunes::addTune(std::string&& tune_name, GuitarTune&& guitar_tune)
{
    m_guitar_tunes.insert(
        std::pair<std::string, GuitarTune>(
            tune_name,
            std::move(guitar_tune)
        )
    );

    std::for_each(
        m_listeners.begin(),
        m_listeners.end(),
        [tune_name](Listener* listener)
        {
            listener->onEvent(TuneAdded{ tune_name });
        }
    );
}

void GuitarTunes::addListener(Listener* listener)
{
    auto list = m_listeners.emplace_back(listener);
}

void GuitarTunes::deleteListener(Listener* listener)
{
    auto listener_it = std::find(m_listeners.begin(), m_listeners.end(), listener);
    if (listener_it != m_listeners.end())
    {
        m_listeners.erase(listener_it);
    }
}

void GuitarTunes::changeTune(std::string tune_name)
{
    m_current_tune = tune_name;

    std::for_each(
        m_listeners.begin(),
        m_listeners.end(),
        [tune_name](Listener* listener)
        {
            listener->onEvent(TuneIsChanged{ tune_name });
        }
    );
}

std::string GuitarTunes::getCurrentTuneName() const
{
    return std::string();
}

GuitarTune GuitarTunes::getTune(std::string&& tune_name) const
{
    return m_guitar_tunes.at(tune_name);
}

GuitarTune GuitarTunes::getCurrentTune() const
{
    return m_guitar_tunes.at(m_current_tune);
}

