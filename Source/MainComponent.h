/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent,
                        public Button::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;
    
    void buttonClicked (Button* buttonThatWasClicked) override;

	File loadFiles(const String stringToShow);
    
    void updateGUI();

	void updateLabelText(File originFile, bool rightChannel, double samplingFrequency);

private:
    //==============================================================================
    // Your private member variables go here...

    ScopedPointer<TextButton> leftButton;
    ScopedPointer<TextButton> rightButton;
    ScopedPointer<Label> nameLabelLeft;
    ScopedPointer<Label> leftAdress;
    ScopedPointer<Label> fsLabelLeft;
    ScopedPointer<Label> nameLabelRight;
    ScopedPointer<Label> rightAdress;
    ScopedPointer<Label> fsLabelRight;
    ScopedPointer<TextButton> stopButton;
    ScopedPointer<GroupComponent> groupComponent;
    ScopedPointer<ToggleButton> monoButton;
    ScopedPointer<ToggleButton> interleveadStereoButton;
    ScopedPointer<ToggleButton> multiMonoStereoButton;

	AudioBuffer<float> audioBufferZero;
	AudioBuffer<float> audioBufferOne;
    
    AudioFormatManager formatManager;
    
    bool fileSelected, shouldBeProcessing;

	dsp::Convolution convolutionEngine;
	dsp::ProcessSpec convolutionProperties;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
