#pragma once
#include<string>
#include<array>
#include<memory>
#include<map>


class GuitarStringData
{
public:
    GuitarStringData() = default;

	GuitarStringData(std::string&& note, float frequency)
		:note(note), frequency(frequency) {};

    std::string note{"None"};
    float frequency{ 0.f };
};


class GuitarTune
{
public:
    GuitarTune(std::string&& note1, float frequency1,
               std::string&& note2, float frequency2,
               std::string&& note3, float frequency3,
               std::string&& note4, float frequency4,
               std::string&& note5, float frequency5,
        std::string&& note6, float frequency6);

private:
    void setString(uint8_t idx, GuitarStringData&& string_data);

    std::array<GuitarStringData, 6> m_guitar_strings;
};


class GuitarTunes
{
public:
    GuitarTunes();

    void add(std::string&& tune_name, GuitarTune&& guitar_tune);

protected:
    std::map<std::string, GuitarTune>   m_guitar_tunes;
    std::string                         m_current_tune;
};