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

	if (const AudioParameterFloat* paramf = dynamic_cast<AudioParameterFloat*> (params[p.kFilterOrder])) {
		createSliderForParam(paramf);
	}

	if (const AudioParameterChoice* paramc = dynamic_cast<AudioParameterChoice*> (params[p.kFilterType])) {
		filterTypeCB = new ComboBox(paramc->name);
		for (int i = 0; i < paramc->choices.size(); i++) {
			filterTypeCB->addItem(paramc->choices[i], i+1);
		}
		filterTypeCB->setSelectedId(1);
		filterTypeCB->addListener(this);
		addAndMakeVisible(filterTypeCB);
	}
	//frequencyResponseDisplay.setName("FrequencyResponseDisplay");

	addAndMakeVisible(&spectrumDisplay);

//	filterResponse = new Path();
	//filterResponse->startNewSubPath(0, 200);
	//filterResponse->lineTo(150, 200);
	//filterResponse->lineTo(250, 300);
	//filterResponse->closeSubPath();


	setSize(500, 400);


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

    //g.setColour (Colours::black);
    //g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
	

	//Array<float> frequencyResponse = processor.getFrequencyResponse();

	////sur x, on mappe 20 à 0 et 20000 à 400 logarithmiquement (trop de h)
	////sur y, on mappe 0 à 200, +15 à 160.

	//float offset = log10f(processor.frequencies[0]);

	//filterResponse->startNewSubPath(0, 250 - frequencyResponse[0]*10);
	//for (int i = 1; i < frequencyResponse.size(); i++) {
	//	
	//	float freq = processor.frequencies[i];
	//	float log_freq = log10f(freq);
	//	float x = (log_freq  - offset)*120;

	//	float response = frequencyResponse[i]*10;
	//	float y = 250 - response;
	//	filterResponse->lineTo(x, y);
	//	
	//	//filterResponse->lineTo(log10f(processor.frequencies[i])-offset, 200 - frequencyResponse[i]);
	//}

	//g.strokePath(*filterResponse, PathStrokeType(2.0f));
	//filterResponse->clear();
}

void NewProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

	paramSliders[processor.kCutoff]->setBounds(5, 5, 100, 50);
	paramSliders[processor.kReso]->setBounds(105, 5, 100, 50);
	paramSliders[processor.kFilterOrder]->setBounds(210, 5, 100, 50);

	filterTypeCB->setBounds(315, 15, 100, 20);

	spectrumDisplay.setBounds(5, 55, 490, 330 );

	/*cutoffSlider.setBounds(50, 150, 100, 100);

	resoSlider.setBounds(250, 150, 100, 100);*/


}

void NewProjectAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
	//const OwnedArray<AudioProcessorParameter>& params = processor.getParameters();
	if (AudioParameterFloat* param= getParameterForSlider(slider))
	{
		const OwnedArray<AudioProcessorParameter>& params = getAudioProcessor()->getParameters();
		const AudioParameterFloat* cutoff = dynamic_cast<AudioParameterFloat*> (params[processor.kCutoff]);

		*param = (float)slider->getValue();
		spectrumDisplay.setFilterResponsePath(processor.frequencies, processor.getFrequencyResponse(),*cutoff);
	}
}
   

void NewProjectAudioProcessorEditor::comboBoxChanged(ComboBox* comboBox)
{
	const OwnedArray<AudioProcessorParameter>& params = processor.getParameters();
	if (comboBox == filterTypeCB) 
	{
		const OwnedArray<AudioProcessorParameter>& params = getAudioProcessor()->getParameters();
		const AudioParameterFloat* cutoff = dynamic_cast<AudioParameterFloat*> (params[processor.kCutoff]);

		AudioParameterChoice* param = dynamic_cast<AudioParameterChoice*> (params[processor.kFilterType]);
		*param = comboBox->getSelectedId()-1;
		spectrumDisplay.setFilterResponsePath(processor.frequencies, processor.getFrequencyResponse(), *cutoff);
	}
}

void NewProjectAudioProcessorEditor::createSliderForParam(const AudioParameterFloat* param, String suffix, juce::Slider::SliderStyle sliderStyle)
{
	Slider* slider = new Slider(sliderStyle, Slider::TextBoxBelow);
	paramSliders.add(slider);
	slider->setRange(param->range.start, param->range.end, param->range.interval);
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


//Path* NewProjectAudioProcessorEditor::getFilterResponsePath()
//{
//	Array<float> frequencyResponse = processor.getFrequencyResponse();
//
//	//sur x, on mappe 20 à 0 et 20000 à 400 logarithmiquement (trop de h)
//	//sur y, on mappe 0 à 200, +15 à 160.
//
//	float offset = log10f(processor.frequencies[0]);
//
//	filterResponse->startNewSubPath(0, 250 - frequencyResponse[0] * 10);
//	for (int i = 1; i < frequencyResponse.size(); i++) {
//
//		float freq = processor.frequencies[i];
//		float log_freq = log10f(freq);
//		float x = (log_freq - offset) * 120;
//
//		float response = frequencyResponse[i] * 10;
//		float y = 250 - response;
//		filterResponse->lineTo(x, y);
//
//		//filterResponse->lineTo(log10f(processor.frequencies[i])-offset, 200 - frequencyResponse[i]);
//	}
//
//	return filterResponse;
//}