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

    
	
	const OwnedArray<AudioProcessorParameter>& params = getAudioProcessor()->getParameters();

	if (const AudioParameterFloat* paramf = dynamic_cast<AudioParameterFloat*> (params[p.kCutoff])) {
		createSliderForParam(paramf, " Hz");
	}
	
	if (const AudioParameterFloat* paramf = dynamic_cast<AudioParameterFloat*> (params[p.kReso])) {
		createSliderForParam(paramf);
	}

	if (const AudioParameterChoice* paramc = dynamic_cast<AudioParameterChoice*> (params[p.kFilterType])) {
		filterTypeCB = new ComboBox(paramc->name);
		for (int i = 0; i < paramc->choices.size(); i++) {
			filterTypeCB->addItem(paramc->choices[i], i+1);
		}
		filterTypeCB->setSelectedId(0);
		filterTypeCB->addListener(this);
		addAndMakeVisible(filterTypeCB);
	}



	setSize(400, 300);


	//paramSliders.add(&cutoffSlider);
	//cutoffSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	//cutoffSlider.setRange(20.0f, 20000.0f);
	//cutoffSlider.setTextValueSuffix(" Hz");
	//cutoffSlider.addListener(this);
	//cutoffSlider.setValue(1000);
	//cutoffSlider.setSkewFactor(0.1);
	//
	//paramSliders.add(&resoSlider);
	//resoSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	//resoSlider.setRange(0.5f, 3-.0f);
	//resoSlider.addListener(this);
	//resoSlider.setValue(0.5);

	//addAndMakeVisible(&cutoffSlider);
	//addAndMakeVisible(&resoSlider);
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

	paramSliders[processor.kCutoff]->setBounds(50, 50, 100, 100);
	paramSliders[processor.kReso]->setBounds(250, 50, 100, 100);

	filterTypeCB->setBounds(50, 150, 100, 20);

	/*cutoffSlider.setBounds(50, 150, 100, 100);

	resoSlider.setBounds(250, 150, 100, 100);*/


}

void NewProjectAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
	//const OwnedArray<AudioProcessorParameter>& params = processor.getParameters();
	if (AudioParameterFloat* param= getParameterForSlider(slider))
	{
		*param = (float)slider->getValue();
	}
}
   

void NewProjectAudioProcessorEditor::comboBoxChanged(ComboBox* comboBox)
{
	const OwnedArray<AudioProcessorParameter>& params = processor.getParameters();
	if (comboBox == filterTypeCB) 
	{
		AudioParameterChoice* param = dynamic_cast<AudioParameterChoice*> (params[processor.kFilterType]);
		*param = comboBox->getSelectedId()-1;
	}
}

void NewProjectAudioProcessorEditor::createSliderForParam(const AudioParameterFloat* param, String suffix, juce::Slider::SliderStyle sliderStyle)
{
	Slider* slider = new Slider(param->name);
	paramSliders.add(slider);
	slider->setRange(param->range.start, param->range.end);
	slider->setSliderStyle(sliderStyle);
	slider->setSkewFactor(param->range.skew);
	slider->setTextValueSuffix(suffix);
	slider->addListener(this);
	slider->setValue(*param);
	addAndMakeVisible(slider);
}



AudioParameterFloat* NewProjectAudioProcessorEditor:: getParameterForSlider(Slider* slider)
{
	const OwnedArray<AudioProcessorParameter>& params = getAudioProcessor()->getParameters();
	return dynamic_cast<AudioParameterFloat*> (params[paramSliders.indexOf(slider)]);
}