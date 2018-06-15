/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioDrawClass.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent,
                        public Button::Listener,
						private Timer
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

	void userTriedToCloseWindow() override;

	File loadFiles (const String stringToShow);
    
	void updateLabelText (File originFile, bool rightChannel, double samplingFrequency);

	void updateThumbnail(bool isStereo, int totalLength, AudioFormatReader* currentReader, AudioBuffer<float> currentAudioBuffer);

	void updateConvolutionEngine(AudioBuffer<float> currentAudioBuffer, AudioFormatReader* currentReader, bool isStereo);

	void timerCallback() override;

	void buttonProcessChange();

private:
    //==============================================================================
    // Your private member variables go here...

    ScopedPointer<TextButton> loadButton;
    ScopedPointer<Label> nameLabelLeft;
    ScopedPointer<Label> leftAdress;
    ScopedPointer<Label> fsLabelLeft;
    ScopedPointer<GroupComponent> groupComponent;
    ScopedPointer<ToggleButton> monoButton;
    ScopedPointer<ToggleButton> interleveadStereoButton;
    ScopedPointer<Label> channelsLabel;
    ScopedPointer<TextButton> processButton;
	ScopedPointer<AlertWindow> errorMessage;
	ScopedPointer<AudioDrawClass> realTimeDraw;

	AudioBuffer<float> audioBufferZero;
    
    AudioFormatManager formatManager;
    
    bool fileSelected, shouldBeProcessing, isBinaural, shouldRepaint;

	AudioThumbnail audioDrawObject;
	AudioThumbnailCache audioDrawCache;

	dsp::Convolution convolutionEngine;
	dsp::ProcessSpec convolutionProperties;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
