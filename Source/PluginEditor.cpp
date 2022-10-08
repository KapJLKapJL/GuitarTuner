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
    m_string_selector(m_tune_selector.getGuitarTunes()),
    m_tuner(m_tune_selector.getGuitarTunes(), m_string_selector.getStringsModel(), m_tuner_modes.getModel()),
    m_difference_indicator(&m_tuner),
    m_freq_updater(&p, &m_tuner)
{
    addAndMakeVisible(m_tune_selector);
    addAndMakeVisible(m_string_selector);
    addAndMakeVisible(m_difference_indicator);
    addAndMakeVisible(m_tuner_modes);
    addAndMakeVisible(m_notes_indicator);

    constexpr int window_width = 300;
    constexpr int window_height = window_width * 2.75 / 4.;
    setSize (window_width, window_height);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void NewProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    auto bounds = getLocalBounds();

    // calc proportions
    constexpr float components_offset_y = 0.25 / 5.5;
    constexpr float components_offset_x = 0.25 / 4.;
    constexpr float default_width =  3.5 / 4.;
    constexpr float default_height = 0.5 / 5.5;
    // tune selector proportions
    constexpr float tune_selector_x = 0. + components_offset_x;
    constexpr float tune_selector_y = 0. + components_offset_y;
    constexpr float tune_selector_width = default_width * 1. / 3.;
    constexpr float tune_selector_height = default_height;
    // tuner modes proportions
    constexpr float tuner_modes_x = tune_selector_x + tune_selector_width;
    constexpr float tuner_modes_y = tune_selector_y;
    constexpr float tuner_modes_width = default_width * 2. / 3.;
    constexpr float tuner_modes_height = default_height;
    // string selector proportions
    constexpr float string_selector_x = 0. + components_offset_x;
    constexpr float string_selector_y = tune_selector_y + tune_selector_height + components_offset_y;
    constexpr float string_selector_width = default_width;
    constexpr float string_selector_height = default_height;
    // difference indicator
    constexpr float difference_indicator_x = 0. + components_offset_x;
    constexpr float difference_indicator_y = string_selector_y + string_selector_height + components_offset_y;
    constexpr float difference_indicator_width = default_width;
    constexpr float difference_indicator_height = difference_indicator_width / 2.;
    // notes indicator
    constexpr float notes_indicator_x = 0. + components_offset_x;
    constexpr float notes_indicator_y = difference_indicator_y + difference_indicator_height + components_offset_y;
    constexpr float notes_indicator_width = default_width;
    constexpr float notes_indicator_height = default_height;

    m_tune_selector.setBounds(
        bounds.getWidth() * tune_selector_x,
        bounds.getHeight() * tune_selector_y,
        bounds.getWidth() * tune_selector_width,
        bounds.getHeight() * tune_selector_height
    );
    m_tuner_modes.setBounds(
        bounds.getWidth() * tuner_modes_x,
        bounds.getHeight() * tuner_modes_y,
        bounds.getWidth() * tuner_modes_width,
        bounds.getHeight() * tuner_modes_height
    );
    m_string_selector.setBounds(
        bounds.getWidth() * string_selector_x,
        bounds.getHeight() * string_selector_y,
        bounds.getWidth() * string_selector_width,
        bounds.getHeight() * string_selector_height
    );
    m_difference_indicator.setBounds(
        bounds.getWidth() * difference_indicator_x,
        bounds.getHeight() * difference_indicator_y,
        bounds.getWidth() * difference_indicator_width,
        bounds.getHeight() * difference_indicator_height
    );
    m_notes_indicator.setBounds(
        bounds.getWidth() * notes_indicator_x,
        bounds.getHeight() * notes_indicator_y,
        bounds.getWidth() * notes_indicator_width,
        bounds.getHeight() * notes_indicator_height
    );


    /*
    m_tune_selector.setBounds(bounds.getX(), bounds.getY(), bounds.getWidth() * 0.4f, bounds.getHeight() * 0.1);
    m_tuner_modes.setBounds(bounds.getX()+ bounds.getWidth() * 0.5f, bounds.getY(), bounds.getWidth() * 0.5f, bounds.getHeight() * 0.1);
    m_string_selector.setBounds(bounds.getX(), bounds.getY() + bounds.getHeight() * 0.1, bounds.getWidth(), bounds.getHeight() * 0.2);
    m_difference_indicator.setBounds(
        bounds.getX(),
        bounds.getY() + bounds.getHeight() * 0.1 + bounds.getHeight() * 0.2 + bounds.getHeight() * 0.1,
        bounds.getWidth(),
        bounds.getHeight() * 0.4
    );
    
    m_notes_indicator.setBounds(
        bounds.getX(),
        bounds.getY() + bounds.getHeight() * 0.1 + bounds.getHeight() * 0.2 + bounds.getHeight() * 0.1 + bounds.getHeight() * 0.4,
        bounds.getWidth(),
        bounds.getHeight() * 0.2
    );
    */
}
