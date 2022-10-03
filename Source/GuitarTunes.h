#pragma once
#include<string>
#include<array>
#include<memory>
#include<map>
#include<list>


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

    std::string getStringName(int idx);
    float       getStringFreq(int idx);

private:
    void setString(uint8_t idx, GuitarStringData&& string_data);

    std::array<GuitarStringData, 6> m_guitar_strings;
};


class GuitarTunes
{
public:
    struct TuneAdded { std::string tune_name; };
    struct TuneIsChanged { std::string tune_name; };

    class Listener
    {
    public:
        Listener() = default;
        virtual ~Listener() = default;

        virtual void onEvent(TuneAdded) {};
        virtual void onEvent(TuneIsChanged) {};
    };


    GuitarTunes(Listener* first);

    void addTune(std::string&& tune_name, GuitarTune&& guitar_tune);

    void addListener(Listener*);
    void deleteListener(Listener*);

    void changeTune(std::string tune_name);

    std::string getCurrentTuneName() const;
    GuitarTune  getTune(std::string&& tune_name) const;
    GuitarTune  getCurrentTune() const;


protected:
    std::map<std::string, GuitarTune>   m_guitar_tunes;
    std::string                         m_current_tune{ "" };

    std::list<Listener*>    m_listeners;
};