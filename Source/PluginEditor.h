/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#include "TuneSelector.h"
#include "StringSelector.h"
#include "Tuner.h"
#include "DifferenceIndicator.h"
#include "FreqUpdater.h"
#include "TunerModes.h"
#include "NotesIndicator.h"

//==============================================================================
/**
*/
class NewProjectAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    NewProjectAudioProcessorEditor (NewProjectAudioProcessor&);
    ~NewProjectAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    StringSelector* getStringSelector() { return &m_string_selector; }

private:
    TuneSelector    m_tune_selector;
    StringSelector  m_string_selector;
    DifferenceIndicator m_difference_indicator;
    TunerModes  m_tuner_modes;
    NotesIndicator  m_notes_indicator;

    Tuner   m_tuner;

    FreqUpdater m_freq_updater;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NewProjectAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectAudioProcessorEditor)
};
