/*
  ==============================================================================

    AudioDrawClass.h
    Created: 12 Jun 2018 8:57:06pm
    Author:  Mateo Yepes

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class AudioDrawClass    : public Component
{
public:
    AudioDrawClass(int updateFrequency);
    ~AudioDrawClass();

    void paint (Graphics&) override;
    void resized() override;

	void updateBufferToDraw(AudioBuffer<float> bufferToReplace);

	void repaintComponent(bool shouldBeRepainting);

	void updateSumArraySize(int newSize);

private:
	AudioBuffer<float> bufferToDraw;
	AudioBuffer<float> tempDrawBuffer;
	ScopedPointer<float> sumArray;
    bool shouldRepaint;
    int internalCounter, sizeMultiplier, refreshRate;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioDrawClass)
};
