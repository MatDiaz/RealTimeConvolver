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
    AudioDrawClass();
    ~AudioDrawClass();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioDrawClass)
};
