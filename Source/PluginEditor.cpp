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

    
	//On récupère les paramètres du plugin 
	const OwnedArray<AudioProcessorParameter>& params = getAudioProcessor()->getParameters();

	//Pour les paramètres flotant, on crée un slider. 
	//Seul les paramètres qui seront affichés au chargement du plugin sont visibles.
	//À noter, la fonction "createSliderForParam" crée un slider et le stocke dans paramSliders.
	if (const AudioParameterFloat* paramf = dynamic_cast<AudioParameterFloat*> (params[p.kCutoff])) {
		createSliderForParam(paramf, " Hz");
	}
	
	if (const AudioParameterFloat* paramf = dynamic_cast<AudioParameterFloat*> (params[p.kReso])) {
		createSliderForParam(paramf);
	}

	if (const AudioParameterFloat* paramf = dynamic_cast<AudioParameterFloat*> (params[p.kFilterOrder])) {
		createSliderForParam(paramf);
	}
	
	if (const AudioParameterFloat* paramf = dynamic_cast<AudioParameterFloat*> (params[p.kFeedbackGain])) {
		createSliderForParam(paramf);
		paramSliders[p.kFeedbackGain]->setVisible(false);//Ici, le paramètre n'est pas utilisé par défaut, donc on le cache.
	}

	//Création du sélecteur de type de filtre.
	if (const AudioParameterChoice* paramc = dynamic_cast<AudioParameterChoice*> (params[p.kFilterType])) {
		filterTypeCB = new ComboBox(paramc->name);
		for (int i = 0; i < paramc->choices.size(); i++) {
			filterTypeCB->addItem(paramc->choices[i], i+1);
		}
		filterTypeCB->setSelectedId(1);
		filterTypeCB->addListener(this);
		addAndMakeVisible(filterTypeCB);
	}

	//On ajoute le composant qui trace la réponse en fréquence.
	addAndMakeVisible(&spectrumDisplay);

	//On défini la taille de l'editor en dernier, car setSize() appelle resize() et il faut donc que tous les components soient définis.
	setSize(500, 400);

}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
	paramSliders.clear(false);
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);

}

void NewProjectAudioProcessorEditor::resized()
{

	//On positionne nos composants:

	//Première ligne, de gauche à droite (avec la visibilité par défaut):
	paramSliders[processor.kCutoff]->setBounds(5, 5, 100, 50);//Visible
	
	paramSliders[processor.kReso]->setBounds(105, 5, 100, 50);//Visible
	paramSliders[processor.kFeedbackGain]->setBounds(105, 5, 100, 50);//Invisible
	
	paramSliders[processor.kFilterOrder]->setBounds(210, 5, 100, 50);//Visible
	
	filterTypeCB->setBounds(315, 15, 100, 20);//Visible

	//Deuxième ligne:
	spectrumDisplay.setBounds(5, 55, 490, 330 );

}

void NewProjectAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
	//const OwnedArray<AudioProcessorParameter>& params = processor.getParameters();
	if (AudioParameterFloat* param= getParameterForSlider(slider))
	{
		const OwnedArray<AudioProcessorParameter>& params = getAudioProcessor()->getParameters();
		const AudioParameterFloat* cutoff = dynamic_cast<AudioParameterFloat*> (params[processor.kCutoff]);

		*param = (float)slider->getValue();
		processor.refreshFilterForDisplay();
		spectrumDisplay.setFilterResponsePath(processor.frequencies, processor.getFrequencyResponse(),*cutoff);
	}
}
   

void NewProjectAudioProcessorEditor::comboBoxChanged(ComboBox* comboBox)
{
	const OwnedArray<AudioProcessorParameter>& params = processor.getParameters();
	if (comboBox == filterTypeCB) 
	{

		//On récupère le paramètre modifié
		const OwnedArray<AudioProcessorParameter>& params = getAudioProcessor()->getParameters();
		AudioParameterChoice* param = dynamic_cast<AudioParameterChoice*> (params[processor.kFilterType]);
	
		//On stocke son ancienne valeur;
		int oldValue = param->getIndex();

		//On modifie sa valeur
		*param = comboBox->getSelectedId()-1;

		//Dans certains cas, il faut changer les potards qu'on affiche.
		if (oldValue == processor.kComb && param->getIndex() != processor.kComb)
		{
			paramSliders[processor.kReso]->setVisible(true);
			paramSliders[processor.kFeedbackGain]->setVisible(false);
		}
		if (param->getIndex() == processor.kComb)
		{
			paramSliders[processor.kReso]->setVisible(false);
			paramSliders[processor.kFeedbackGain]->setVisible(true);
		}
		
		
		//On calcule les coefficients du filtre avec les nouveaux paramètres pour être sûr de tracer le bon spectre d'amplitude
		processor.refreshFilterForDisplay();
		
		//On calcule le spectre d'amplitude et on demande gentiment à le retracer quand il y aura l'occasion
		const AudioParameterFloat* cutoff = dynamic_cast<AudioParameterFloat*> (params[processor.kCutoff]);
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