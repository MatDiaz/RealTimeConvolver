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

    addAndMakeVisible (loadButton = new TextButton ("loadButton"));
    loadButton->setButtonText (CharPointer_UTF8 ("Cargar IR Mono/Est\xc3\xa9ro"));
    loadButton->addListener (this);

    loadButton->setBounds (127, 130, 150, 24);

    addAndMakeVisible (nameLabelLeft = new Label ("nameLabelLeft",
                                                  TRANS("Nombre:")));
    nameLabelLeft->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    nameLabelLeft->setJustificationType (Justification::centredLeft);
    nameLabelLeft->setEditable (false, false, false);
    nameLabelLeft->setColour (TextEditor::textColourId, Colours::black);
    nameLabelLeft->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    nameLabelLeft->setBounds (24, 200, 344, 24);

    addAndMakeVisible (leftAdress = new Label ("leftAdress",
                                               CharPointer_UTF8 ("Direcci\xc3\xb3n: ")));
    leftAdress->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    leftAdress->setJustificationType (Justification::centredLeft);
    leftAdress->setEditable (false, false, false);
    leftAdress->setColour (TextEditor::textColourId, Colours::black);
    leftAdress->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    leftAdress->setBounds (24, 168, 344, 24);

    addAndMakeVisible (fsLabelLeft = new Label ("fsLabelLeft",
                                                TRANS("F. Muestreo: ")));
    fsLabelLeft->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    fsLabelLeft->setJustificationType (Justification::centredLeft);
    fsLabelLeft->setEditable (false, false, false);
    fsLabelLeft->setColour (TextEditor::textColourId, Colours::black);
    fsLabelLeft->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    fsLabelLeft->setBounds (24, 264, 344, 24);

    addAndMakeVisible (groupComponent = new GroupComponent ("new group",
                                                            String()));

    groupComponent->setBounds (24, 59, 360, 56);

    addAndMakeVisible (monoButton = new ToggleButton ("monoButton"));
    monoButton->setButtonText (CharPointer_UTF8 ("IR Mono/Est\xc3\xa9reo"));
    monoButton->setRadioGroupId (1);
    monoButton->addListener (this);

    monoButton->setBounds (32, 78, 152, 24);

    addAndMakeVisible (interleveadStereoButton = new ToggleButton ("interleveadStereoButton"));
    interleveadStereoButton->setButtonText (TRANS("IR Muti-Mono"));
    interleveadStereoButton->setRadioGroupId (1);
    interleveadStereoButton->addListener (this);

    interleveadStereoButton->setBounds (216, 78, 160, 24);

    addAndMakeVisible (channelsLabel = new Label ("channelsLabel",
                                                  CharPointer_UTF8 ("Configuraci\xc3\xb3n\n")));
    channelsLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    channelsLabel->setJustificationType (Justification::centredLeft);
    channelsLabel->setEditable (false, false, false);
    channelsLabel->setColour (TextEditor::textColourId, Colours::black);
    channelsLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    channelsLabel->setBounds (24, 232, 344, 24);

    addAndMakeVisible (processButton = new TextButton ("processButton"));
    processButton->setButtonText (TRANS("Procesar"));
    processButton->addListener (this);

    processButton->setBounds (32, 488, 344, 24);


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

    loadButton = nullptr;
    nameLabelLeft = nullptr;
    leftAdress = nullptr;
    fsLabelLeft = nullptr;
    groupComponent = nullptr;
    monoButton = nullptr;
    interleveadStereoButton = nullptr;
    channelsLabel = nullptr;
    processButton = nullptr;


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

    {
        float x = 29.0f, y = 305.0f, width = 356.0f, height = 168.0f;
        Colour fillColour = Colour (0xff3c3c3c);
        Colour strokeColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 0.500f);
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

    if (buttonThatWasClicked == loadButton)
    {
        //[UserButtonCode_loadButton] -- add your button handler code here..
        //[/UserButtonCode_loadButton]
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
    else if (buttonThatWasClicked == processButton)
    {
        //[UserButtonCode_processButton] -- add your button handler code here..
        //[/UserButtonCode_processButton]
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
    <ROUNDRECT pos="29 305 356 168" cornerSize="10.00000000000000000000" fill="solid: ff3c3c3c"
               hasStroke="1" stroke="0.5, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <TEXTBUTTON name="loadButton" id="c84767a5b1b1a169" memberName="loadButton"
              virtualName="" explicitFocusOrder="0" pos="127 130 150 24" buttonText="Cargar IR Mono/Est&#233;ro"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="nameLabelLeft" id="1ca1aba907c4db01" memberName="nameLabelLeft"
         virtualName="" explicitFocusOrder="0" pos="24 200 344 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Nombre:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="33"/>
  <LABEL name="leftAdress" id="a59c2a0fe6802c47" memberName="leftAdress"
         virtualName="" explicitFocusOrder="0" pos="24 168 344 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Direcci&#243;n: " editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <LABEL name="fsLabelLeft" id="fdffeefa580fe0f9" memberName="fsLabelLeft"
         virtualName="" explicitFocusOrder="0" pos="24 264 344 24" edTextCol="ff000000"
         edBkgCol="0" labelText="F. Muestreo: " editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <GROUPCOMPONENT name="new group" id="992b46563bcbb59b" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="24 59 360 56" title=""/>
  <TOGGLEBUTTON name="monoButton" id="69897ee5cb8fc8f6" memberName="monoButton"
                virtualName="" explicitFocusOrder="0" pos="32 78 152 24" buttonText="IR Mono/Est&#233;reo"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <TOGGLEBUTTON name="interleveadStereoButton" id="eda4422c7fb17ef5" memberName="interleveadStereoButton"
                virtualName="" explicitFocusOrder="0" pos="216 78 160 24" buttonText="IR Muti-Mono"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <LABEL name="channelsLabel" id="74d3b60a39986aa2" memberName="channelsLabel"
         virtualName="" explicitFocusOrder="0" pos="24 232 344 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Configuraci&#243;n&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="processButton" id="d1c73ddfc2004d74" memberName="processButton"
              virtualName="" explicitFocusOrder="0" pos="32 488 344 24" buttonText="Procesar"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
