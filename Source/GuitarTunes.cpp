#include "GuitarTunes.h"

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

GuitarTunes::GuitarTunes()
{
    add(
        "E-standart",
        GuitarTune(
            "E", 329.6f,
            "B", 247.0f,
            "G", 196.0f,
            "D", 146.8f,
            "A", 110.0f,
            "E", 82.41f
        )
    );
    add(
        "Drop-D",
        GuitarTune(
            "E", 329.6f,
            "B", 247.0f,
            "G", 196.0f,
            "D", 146.8f,
            "A", 110.0f,
            "D", 73.43f)
    );

    m_current_tune = "E-standart";
}

void GuitarTunes::add(std::string&& tune_name, GuitarTune&& guitar_tune)
{
    m_guitar_tunes.insert(
        std::pair<std::string, GuitarTune>(
            std::move(tune_name),
            std::move(guitar_tune)
        )
    );
}
