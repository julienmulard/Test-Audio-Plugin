/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	//Youpi
    setSize (400, 300);

	cutoffSlider.setSliderStyle(Slider::Rotary);
	cutoffSlider.setRange(20, 20000);
	cutoffSlider.setTextValueSuffix(" Hz");
	//cutoffSlider.addListener(this);
	cutoffSlider.setValue(1000);
	

	resoSlider.setSliderStyle(Slider::Rotary);
	resoSlider.setRange(0.5, 10);
	//resoSlider.addListener(this);
	resoSlider.setValue(0.5);

	addAndMakeVisible(&cutoffSlider);
	addAndMakeVisible(&resoSlider);

}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);

    g.setColour (Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);

	
	cutoffSlider.setBounds(50, 150, 100, 100);
	
	resoSlider.setBounds(250, 150, 100, 100);
}

void NewProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
