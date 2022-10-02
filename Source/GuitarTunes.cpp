#include "GuitarTunes.h"

#include <algorithm>


GuitarTune::GuitarTune(std::string&& note1, float frequency1, std::string&& note2, float frequency2, std::string&& note3, float frequency3, std::string&& note4, float frequency4, std::string&& note5, float frequency5, std::string&& note6, float frequency6)
{
    setString(0, GuitarStringData(std::move(note1), frequency1));
    setString(1, GuitarStringData(std::move(note2), frequency2));
    setString(2, GuitarStringData(std::move(note3), frequency3));
    setString(3, GuitarStringData(std::move(note4), frequency4));
    setString(4, GuitarStringData(std::move(note5), frequency5));
    setString(5, GuitarStringData(std::move(note6), frequency6));
}

void GuitarTune::setString(uint8_t idx, GuitarStringData&& string_data)
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
    m_listeners.emplace_back(listener);
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

std::string GuitarTunes::getCurrentTune() const
{
    return m_current_tune;
}
