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
	
	paramSliders.add(&cutoffSlider);
	cutoffSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	cutoffSlider.setRange(20.0f, 20000.0f);
	cutoffSlider.setTextValueSuffix(" Hz");
	cutoffSlider.addListener(this);
	cutoffSlider.setValue(1000);
	cutoffSlider.setSkewFactor(0.1);
	
	paramSliders.add(&resoSlider);
	resoSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	resoSlider.setRange(0.5f, 3-.0f);
	resoSlider.addListener(this);
	resoSlider.setValue(0.5);

	addAndMakeVisible(&cutoffSlider);
	addAndMakeVisible(&resoSlider);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
	paramSliders.clear(false);
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);

    g.setColour (Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);

	
	
}

void NewProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

	cutoffSlider.setBounds(50, 150, 100, 100);

	resoSlider.setBounds(250, 150, 100, 100);


}

void NewProjectAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
	const OwnedArray<AudioProcessorParameter>& params = processor.getParameters();
	if (AudioParameterFloat* param= getParameterForSlider(slider))
	{
		*param = (float)slider->getValue();
	}
}
     

AudioParameterFloat* NewProjectAudioProcessorEditor:: getParameterForSlider(Slider* slider)
{
	const OwnedArray<AudioProcessorParameter>& params = getAudioProcessor()->getParameters();
	return dynamic_cast<AudioParameterFloat*> (params[paramSliders.indexOf(slider)]);
}