/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor(NewProjectAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p),
    m_string_selector(m_tune_selector.getGuitarTunes())
{
    auto tunes = m_tune_selector.getGuitarTunes();

    tunes->addTune(
        "E-standart",
        GuitarTune(
            "E", 329.6f,
            "B", 247.0f,
            "G", 196.0f,
            "D", 146.8f,
            "A", 110.0f,
            "E", 82.41f)
    );
    tunes->changeTune("E-standart");
    tunes->addTune(
        "Drop-D",
        GuitarTune(
            "E", 329.6f,
            "B", 247.0f,
            "G", 196.0f,
            "D", 146.8f,
            "A", 110.0f,
            "D", 73.43f)
    );


    addAndMakeVisible(m_tune_selector);
    addAndMakeVisible(m_string_selector);

    addAndMakeVisible(m_tune);
    m_tune.onClick = [this] {
        getStringSelector()->getStringsModel()->onEvent(StringsModel::IsTuned());
    };

    setSize (400, 300);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void NewProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    auto bounds = getLocalBounds();
    m_tune_selector.setBounds(bounds.getX(), bounds.getY(), bounds.getWidth() * 0.4f, bounds.getHeight() * 0.1);
    m_string_selector.setBounds(bounds.getX(), bounds.getY() + bounds.getHeight() * 0.1, bounds.getWidth(), bounds.getHeight() * 0.4);
    m_tune.setBounds(bounds.getX(), bounds.getY() + bounds.getHeight() * 0.1 + bounds.getHeight() * 0.4, bounds.getWidth() * 0.4f, bounds.getHeight() * 0.1);
}
