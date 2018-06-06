/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.2.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "GUIcomponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
GUIcomponent::GUIcomponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (leftButton = new TextButton ("leftButton"));
    leftButton->setButtonText (TRANS("IR Left"));
    leftButton->addListener (this);

    leftButton->setBounds (24, 176, 150, 24);

    addAndMakeVisible (rightButton = new TextButton ("new button"));
    rightButton->setButtonText (TRANS("IR Right"));
    rightButton->addListener (this);

    rightButton->setBounds (24, 320, 150, 24);

    addAndMakeVisible (nameLabelLeft = new Label ("nameLabelLeft",
                                                  TRANS("Nombre:")));
    nameLabelLeft->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    nameLabelLeft->setJustificationType (Justification::centredLeft);
    nameLabelLeft->setEditable (false, false, false);
    nameLabelLeft->setColour (TextEditor::textColourId, Colours::black);
    nameLabelLeft->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    nameLabelLeft->setBounds (24, 248, 344, 24);

    addAndMakeVisible (leftAdress = new Label ("leftAdress",
                                               CharPointer_UTF8 ("Direcci\xc3\xb3n: ")));
    leftAdress->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    leftAdress->setJustificationType (Justification::centredLeft);
    leftAdress->setEditable (false, false, false);
    leftAdress->setColour (TextEditor::textColourId, Colours::black);
    leftAdress->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    leftAdress->setBounds (24, 216, 344, 24);

    addAndMakeVisible (fsLabelLeft = new Label ("fsLabelLeft",
                                                TRANS("F. Muestreo: ")));
    fsLabelLeft->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    fsLabelLeft->setJustificationType (Justification::centredLeft);
    fsLabelLeft->setEditable (false, false, false);
    fsLabelLeft->setColour (TextEditor::textColourId, Colours::black);
    fsLabelLeft->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    fsLabelLeft->setBounds (24, 280, 344, 24);

    addAndMakeVisible (nameLabelRight = new Label ("nameLabelRight",
                                                   TRANS("Nombre:")));
    nameLabelRight->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    nameLabelRight->setJustificationType (Justification::centredLeft);
    nameLabelRight->setEditable (false, false, false);
    nameLabelRight->setColour (TextEditor::textColourId, Colours::black);
    nameLabelRight->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    nameLabelRight->setBounds (24, 389, 344, 24);

    addAndMakeVisible (rightAdress = new Label ("rightAdress",
                                                CharPointer_UTF8 ("Direcci\xc3\xb3n: ")));
    rightAdress->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    rightAdress->setJustificationType (Justification::centredLeft);
    rightAdress->setEditable (false, false, false);
    rightAdress->setColour (TextEditor::textColourId, Colours::black);
    rightAdress->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    rightAdress->setBounds (24, 360, 344, 24);

    addAndMakeVisible (fsLabelRight = new Label ("fsLabelRight",
                                                 TRANS("F. Muestreo: ")));
    fsLabelRight->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    fsLabelRight->setJustificationType (Justification::centredLeft);
    fsLabelRight->setEditable (false, false, false);
    fsLabelRight->setColour (TextEditor::textColourId, Colours::black);
    fsLabelRight->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    fsLabelRight->setBounds (24, 420, 344, 24);

    addAndMakeVisible (stopButton = new TextButton ("stopButton"));
    stopButton->setButtonText (TRANS("STAHP"));
    stopButton->addListener (this);

    stopButton->setBounds (24, 464, 344, 24);

    addAndMakeVisible (groupComponent = new GroupComponent ("new group",
                                                            String()));

    groupComponent->setBounds (16, 56, 368, 96);

    addAndMakeVisible (monoButton = new ToggleButton ("monoButton"));
    monoButton->setButtonText (TRANS("IR Mono"));
    monoButton->setRadioGroupId (1);
    monoButton->addListener (this);

    monoButton->setBounds (32, 80, 88, 24);

    addAndMakeVisible (interleveadStereoButton = new ToggleButton ("interleveadStereoButton"));
    interleveadStereoButton->setButtonText (CharPointer_UTF8 ("IR Est\xc3\xa9reo Entrelazado"));
    interleveadStereoButton->setRadioGroupId (1);
    interleveadStereoButton->addListener (this);

    interleveadStereoButton->setBounds (173, 80, 184, 24);

    addAndMakeVisible (multiMonoStereoButton = new ToggleButton ("multiMonoStereoButton"));
    multiMonoStereoButton->setButtonText (CharPointer_UTF8 ("IR Est\xc3\xa9reo Multi-Mono"));
    multiMonoStereoButton->setRadioGroupId (1);
    multiMonoStereoButton->addListener (this);

    multiMonoStereoButton->setBounds (32, 117, 184, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (400, 530);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

GUIcomponent::~GUIcomponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    leftButton = nullptr;
    rightButton = nullptr;
    nameLabelLeft = nullptr;
    leftAdress = nullptr;
    fsLabelLeft = nullptr;
    nameLabelRight = nullptr;
    rightAdress = nullptr;
    fsLabelRight = nullptr;
    stopButton = nullptr;
    groupComponent = nullptr;
    monoButton = nullptr;
    interleveadStereoButton = nullptr;
    multiMonoStereoButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void GUIcomponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff242424));

    {
        int x = 28, y = 16, width = 350, height = 32;
        String text (TRANS("Real Time Convolver"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (27.40f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void GUIcomponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void GUIcomponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == leftButton)
    {
        //[UserButtonCode_leftButton] -- add your button handler code here..
        //[/UserButtonCode_leftButton]
    }
    else if (buttonThatWasClicked == rightButton)
    {
        //[UserButtonCode_rightButton] -- add your button handler code here..
        //[/UserButtonCode_rightButton]
    }
    else if (buttonThatWasClicked == stopButton)
    {
        //[UserButtonCode_stopButton] -- add your button handler code here..
        //[/UserButtonCode_stopButton]
    }
    else if (buttonThatWasClicked == monoButton)
    {
        //[UserButtonCode_monoButton] -- add your button handler code here..
        //[/UserButtonCode_monoButton]
    }
    else if (buttonThatWasClicked == interleveadStereoButton)
    {
        //[UserButtonCode_interleveadStereoButton] -- add your button handler code here..
        //[/UserButtonCode_interleveadStereoButton]
    }
    else if (buttonThatWasClicked == multiMonoStereoButton)
    {
        //[UserButtonCode_multiMonoStereoButton] -- add your button handler code here..
        //[/UserButtonCode_multiMonoStereoButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="GUIcomponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="400" initialHeight="530">
  <BACKGROUND backgroundColour="ff242424">
    <TEXT pos="28 16 350 32" fill="solid: ffffffff" hasStroke="0" text="Real Time Convolver"
          fontname="Default font" fontsize="27.39999999999999857891" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
  </BACKGROUND>
  <TEXTBUTTON name="leftButton" id="c84767a5b1b1a169" memberName="leftButton"
              virtualName="" explicitFocusOrder="0" pos="24 176 150 24" buttonText="IR Left"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="ec47f28c6be456ad" memberName="rightButton"
              virtualName="" explicitFocusOrder="0" pos="24 320 150 24" buttonText="IR Right"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="nameLabelLeft" id="1ca1aba907c4db01" memberName="nameLabelLeft"
         virtualName="" explicitFocusOrder="0" pos="24 248 344 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Nombre:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="33"/>
  <LABEL name="leftAdress" id="a59c2a0fe6802c47" memberName="leftAdress"
         virtualName="" explicitFocusOrder="0" pos="24 216 344 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Direcci&#243;n: " editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <LABEL name="fsLabelLeft" id="fdffeefa580fe0f9" memberName="fsLabelLeft"
         virtualName="" explicitFocusOrder="0" pos="24 280 344 24" edTextCol="ff000000"
         edBkgCol="0" labelText="F. Muestreo: " editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <LABEL name="nameLabelRight" id="1cb4e6111d21cf0c" memberName="nameLabelRight"
         virtualName="" explicitFocusOrder="0" pos="24 389 344 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Nombre:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="33"/>
  <LABEL name="rightAdress" id="c461b69f88aabfb" memberName="rightAdress"
         virtualName="" explicitFocusOrder="0" pos="24 360 344 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Direcci&#243;n: " editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <LABEL name="fsLabelRight" id="1f8148501ba592c2" memberName="fsLabelRight"
         virtualName="" explicitFocusOrder="0" pos="24 420 344 24" edTextCol="ff000000"
         edBkgCol="0" labelText="F. Muestreo: " editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="stopButton" id="2ea543e027d3d15c" memberName="stopButton"
              virtualName="" explicitFocusOrder="0" pos="24 464 344 24" buttonText="STAHP"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <GROUPCOMPONENT name="new group" id="992b46563bcbb59b" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="16 56 368 96" title=""/>
  <TOGGLEBUTTON name="monoButton" id="69897ee5cb8fc8f6" memberName="monoButton"
                virtualName="" explicitFocusOrder="0" pos="32 80 88 24" buttonText="IR Mono"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <TOGGLEBUTTON name="interleveadStereoButton" id="eda4422c7fb17ef5" memberName="interleveadStereoButton"
                virtualName="" explicitFocusOrder="0" pos="173 80 184 24" buttonText="IR Est&#233;reo Entrelazado"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <TOGGLEBUTTON name="multiMonoStereoButton" id="7ba3f9175a3e823b" memberName="multiMonoStereoButton"
                virtualName="" explicitFocusOrder="0" pos="32 117 184 24" buttonText="IR Est&#233;reo Multi-Mono"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
