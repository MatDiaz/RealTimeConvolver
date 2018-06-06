/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    
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
	monoButton->setToggleState(true, dontSendNotification);
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

    setSize (400, 530);


    // specify the number of input and output channels that we want to open
    setAudioChannels (2, 2);
    
    updateGUI();
}

MainComponent::~MainComponent()
{   
    
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

    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here
    
    const int numChannels = bufferToFill.buffer->getNumChannels();
    
    if (numChannels == 2)
    {
        float* channelL = bufferToFill.buffer->getWritePointer(0);
        float* channelR = bufferToFill.buffer->getWritePointer(1);
        
        for (int i = 0; i < bufferToFill.buffer->getNumSamples(); i++)
        {
            
        }
    }
    
    // For more details, see the help for AudioProcessor::getNextAudioBlock()

    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)
    bufferToFill.clearActiveBufferRegion();
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

void MainComponent::updateGUI()
{
	bool isMono = monoButton->getToggleState();
	bool isStereoInterleaved = interleveadStereoButton->getToggleState();
	bool isStereoMultiMono = multiMonoStereoButton->getToggleState();
    
    if (isMono)
    {
        leftButton->setButtonText("IR Mono");
        rightButton->setEnabled(false);
        
        nameLabelRight->setEnabled(false);
        rightAdress->setEnabled(false);
        fsLabelRight->setEnabled(false);

		rightButton->setVisible(true);

		nameLabelRight->setVisible(true);
		rightAdress->setVisible(true);
		fsLabelRight->setVisible(true);
    }
    else if (isStereoMultiMono)
    {
        rightButton->setEnabled(true);
        leftButton->setButtonText("IR Left");
        rightButton->setButtonText("IR Right");
        
        nameLabelRight->setEnabled(true);
        rightAdress->setEnabled(true);
        fsLabelRight->setEnabled(true);

		rightButton->setVisible(true);

		nameLabelRight->setVisible(true);
		rightAdress->setVisible(true);
		fsLabelRight->setVisible(true);
    }
	else if (isStereoInterleaved)
	{
		leftButton->setButtonText(CharPointer_UTF8("IR Est\xc3\xa9reo"));
		rightButton->setVisible(false);

		nameLabelRight->setVisible(false);
		rightAdress->setVisible(false);
		fsLabelRight->setVisible(false);
	}
}

void MainComponent::buttonClicked (Button* buttonThatWasClicked)
{

	if (buttonThatWasClicked == leftButton)
	{
		if (monoButton->getToggleState())
		{
			File monoFile = loadFiles("Ingrese Archivo Mono");
		}
		else if (interleveadStereoButton->getToggleState())
		{
			File stereoFile = loadFiles("Ingrese Archivo Estereo");
		}
		else if (multiMonoStereoButton->getToggleState())
		{
			File fileL = loadFiles("Ingrese Canal L");
		}
    }

    else if (buttonThatWasClicked == rightButton)
    {
		File fileR = loadFiles("Ingrese Canal R");
    }
    else if (buttonThatWasClicked == stopButton)
    {
		shutdownAudio();
    }
    else if (buttonThatWasClicked == monoButton)
    {
		updateGUI();
    }
    else if (buttonThatWasClicked == interleveadStereoButton)
    {
		updateGUI();
    }
    else if (buttonThatWasClicked == multiMonoStereoButton)
    {
		updateGUI();
    }   
}

File MainComponent::loadFiles(const String stringToShow)
{
	FileChooser newFileChooser(stringToShow, File::getSpecialLocation(File::userDesktopDirectory), ".wav");

	if (newFileChooser.browseForFileToOpen())
	{
		File newFile = newFileChooser.getResult();
	}

}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
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
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
