/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

#include "SpectrumDisplay.h"


//==============================================================================
/**
*/
class NewProjectAudioProcessorEditor  : public AudioProcessorEditor,
										public SliderListener,
										public ComboBoxListener
{
public:
    NewProjectAudioProcessorEditor (NewProjectAudioProcessor&);
    ~NewProjectAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NewProjectAudioProcessor& processor;

	Slider cutoffSlider;
	//Label cutoffLabel;

	Slider resoSlider;
	//Label resoLabel;

	ComboBox* filterTypeCB;

	SpectrumDisplay spectrumDisplay;

	void sliderValueChanged(Slider* slider) override;

	void comboBoxChanged(ComboBox* comboBox) override;

	OwnedArray<Slider> paramSliders;
	
	//Path* filterResponse;

	AudioParameterFloat* getParameterForSlider(Slider* slider);

	void createSliderForParam(const AudioParameterFloat* param, String suffix = "", juce::Slider::SliderStyle sliderStyle = Slider::RotaryVerticalDrag);
	//void createSliderForParam(const AudioParameterInt* param, String suffix = "", juce::Slider::SliderStyle sliderStyle = Slider::RotaryVerticalDrag);

	
	//Path* getFilterResponsePath();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
