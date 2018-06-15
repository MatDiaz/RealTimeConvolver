/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent():
fileSelected(false), shouldBeProcessing(false), isBinaural(false), shouldRepaint(false)
,audioDrawObject(256, formatManager, audioDrawCache), audioDrawCache(1)
{
    addAndMakeVisible (loadButton = new TextButton ("loadButton"));
    loadButton->setButtonText (CharPointer_UTF8("Cargar IR Mono/Est\xc3\xa9reo"));
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
    monoButton->setButtonText (CharPointer_UTF8("IR Mono/Est\xc3\xa9reo"));
    monoButton->setRadioGroupId (1);
	monoButton->setToggleState(true, dontSendNotification);
    monoButton->addListener (this);

    monoButton->setBounds (32, 78, 152, 24);

    addAndMakeVisible (interleveadStereoButton = new ToggleButton ("interleveadStereoButton"));
    interleveadStereoButton->setButtonText (TRANS("IR Muti-Mono"));
    interleveadStereoButton->setRadioGroupId (1);
    interleveadStereoButton->addListener (this);

    interleveadStereoButton->setBounds (216, 78, 160, 24);

    addAndMakeVisible (channelsLabel = new Label ("channelsLabel",
		CharPointer_UTF8("Configuraci\xc3\xb3n\n")));
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

	addAndMakeVisible (errorMessage = new AlertWindow("Error", "Error generico", AlertWindow::WarningIcon, nullptr));
	errorMessage->setEscapeKeyCancels(true);

	addAndMakeVisible(realTimeDraw = new AudioDrawClass(3));

    setSize (400, 530);

    setAudioChannels (2, 2);
    
    formatManager.registerBasicFormats();

	startTimer(60);
}

MainComponent::~MainComponent()
{	
	loadButton = nullptr;
	nameLabelLeft = nullptr;
	leftAdress = nullptr;
	fsLabelLeft = nullptr;
	groupComponent = nullptr;
	monoButton = nullptr;
	interleveadStereoButton = nullptr;
	channelsLabel = nullptr;
	processButton = nullptr;

    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
	convolutionProperties.sampleRate = sampleRate;
	convolutionProperties.maximumBlockSize = samplesPerBlockExpected;
	convolutionProperties.numChannels = 2;
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
	if (processButton->getToggleState())
	{
		dsp::AudioBlock<float> tempAudioBlock(*bufferToFill.buffer);
		dsp::ProcessContextReplacing<float> ctx(tempAudioBlock);
		convolutionEngine.process(ctx);
	}
	else
	{
		bufferToFill.clearActiveBufferRegion();
	}
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

void MainComponent::updateLabelText(File originFile, bool rightChannel, double samplingFrequency)
{
	String newName, newAddress, newFs, newConfig;
	newName = "Nombre: " + originFile.getFileName();
	newAddress = CharPointer_UTF8("Direcci\xc3\xb3n: ");
	newAddress = newAddress + originFile.getFullPathName();
	newFs = "F.Muestreo: " + String(samplingFrequency) + " Hz";

	nameLabelLeft->setText(newName, dontSendNotification);
	leftAdress->setText(newAddress, dontSendNotification);
	fsLabelLeft->setText(newFs, dontSendNotification);
	
	if (rightChannel){ channelsLabel->setText(CharPointer_UTF8("Configuraci\xc3\xb3n: Est\xc3\xa9reo"), dontSendNotification);}
	else { channelsLabel->setText(CharPointer_UTF8("Configuraci\xc3\xb3n: Mono"), dontSendNotification);}
}

void MainComponent::updateThumbnail(bool isStereo, int totalLength ,AudioFormatReader* currentReader, AudioBuffer<float> currentAudioBuffer)
{
	int currentChannels;
	isStereo ? currentChannels = 2 : currentChannels = 1;
	audioDrawObject.reset(currentChannels, currentReader->sampleRate);
	shouldRepaint = true;
	repaint();
}

void MainComponent::updateConvolutionEngine(AudioBuffer<float> currentAudioBuffer, AudioFormatReader* currentReader, bool isStereo)
{	
	convolutionEngine.prepare(convolutionProperties);
	convolutionEngine.copyAndLoadImpulseResponseFromBuffer(audioBufferZero, currentReader->sampleRate, isStereo, false, false, 0);
}

void MainComponent::timerCallback()
{
	if (processButton->getToggleState())
	{
		
	}
}

void MainComponent::buttonProcessChange()
{
    if (processButton->getToggleState())
    {
        processButton->setToggleState(false, dontSendNotification);
        processButton->setButtonText("Procesar");
		shouldRepaint = true;
    }
    else
    {
        processButton->setToggleState(true, dontSendNotification);
		shouldRepaint = false;
        processButton->setButtonText("Detener");
    }

	repaint();
}

void MainComponent::buttonClicked (Button* buttonThatWasClicked)
{	

	if (buttonThatWasClicked == loadButton)
    {
        if (processButton->getToggleState()){buttonProcessChange();}

        File outputFile, outputFileL, outputFileR;
        
		if (monoButton->getToggleState())
		{ 
			outputFile = loadFiles("Ingrese Archivo Mono o Estereo");

			if (fileSelected)
			{
				convolutionEngine.reset();

				ScopedPointer<AudioFormatReader> audioReadOperator;

				audioReadOperator = formatManager.createReaderFor(outputFile);

				int audioLength = (int)audioReadOperator->lengthInSamples;

				audioBufferZero.setSize(audioReadOperator->numChannels, audioLength);

				(audioReadOperator->numChannels == 2) ? isBinaural = true : isBinaural = false;

				audioReadOperator->read(&audioBufferZero, 0, audioLength, 0, true, isBinaural);

				updateLabelText(outputFile, isBinaural, audioReadOperator->sampleRate);
				updateThumbnail(isBinaural, audioLength, audioReadOperator, audioBufferZero);
				updateConvolutionEngine(audioBufferZero, audioReadOperator, isBinaural);
			}
			else{ errorMessage->showMessageBoxAsync(AlertWindow::WarningIcon, "Error", "Ningun Archivo Seleccionado", "Ok", nullptr); }
		}
		else if (interleveadStereoButton->getToggleState())
		{
			outputFileL = loadFiles("Ingrese Archivo L");
			if (fileSelected) { outputFileR = loadFiles("Ingrese Archivo R"); }
			else { errorMessage->showMessageBoxAsync(AlertWindow::WarningIcon, "Error", "Ningun Archivo Seleccionado", "Ok", nullptr); }

			if (fileSelected)
			{	
				convolutionEngine.reset();

				ScopedPointer<AudioFormatReader> audioReadOperatorLeft, audioReadOperatorRight;
				audioReadOperatorLeft = formatManager.createReaderFor(outputFileL);
				audioReadOperatorRight = formatManager.createReaderFor(outputFileR);
                
                int audioLength = (int)audioReadOperatorLeft->lengthInSamples;
                
                OwnedArray<AudioFormatReader> audioArrayHolder;
                
                audioArrayHolder.add(audioReadOperatorRight);
                audioArrayHolder.add(audioReadOperatorLeft);
                
                audioBufferZero.setSize(2, audioLength);
                
                for (int i = 0; i < audioArrayHolder.size(); i++)
                {
                    AudioBuffer<float> tempAudioBuffer;
                    tempAudioBuffer.setSize(1, audioLength);
                    audioArrayHolder[i]->read(&tempAudioBuffer, 0, audioLength, 0, true, false);
                    audioBufferZero.copyFrom(i, 0, tempAudioBuffer, 0, 0, audioLength);
                }

				updateConvolutionEngine(audioBufferZero, audioArrayHolder[0], isBinaural);
				updateThumbnail(true, audioLength, audioArrayHolder[0], audioBufferZero);
				updateLabelText(outputFileL, true, audioArrayHolder[0]->sampleRate);
                
                audioArrayHolder.clearQuick(false);
			}
			else{ errorMessage->showMessageBoxAsync(AlertWindow::WarningIcon, "Error", "Ningun Archivo Seleccionado", "Ok", nullptr); }
		}
    }
    else if (buttonThatWasClicked == monoButton)
    {
		loadButton->setButtonText(CharPointer_UTF8("Cargar IR Mono/Est\xc3\xa9reo"));
    }
    else if (buttonThatWasClicked == interleveadStereoButton)
    {
		loadButton->setButtonText("Cargar IR Multi-Mono");
    }
	else if (buttonThatWasClicked == processButton)
	{
        buttonProcessChange();
	}
}

void MainComponent::userTriedToCloseWindow()
{
	if (processButton->getToggleState()) { buttonProcessChange(); }
}

File MainComponent::loadFiles(const String stringToShow)
{
	FileChooser newFileChooser(stringToShow, File::getSpecialLocation(File::userDesktopDirectory), "*.wav");
    
    File newFile;

	if (newFileChooser.browseForFileToOpen())
    {
		newFile = newFileChooser.getResult();
        fileSelected = true;
    }
    else
    {
        fileSelected = false;
    }
    
    return newFile;
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    g.fillAll (Colour (0xff242424));

    {
        int x = 28, y = 16, width = 350, height = 32;
        String text (TRANS("Real Time Convolver"));
        Colour fillColour = Colours::white;
        g.setColour (fillColour);
        g.setFont (Font (27.40f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        float x = 29.0f, y = 305.0f, width = 356.0f, height = 168.0f;
        Colour fillColour = Colour (0xff3c3c3c);
        Colour strokeColour = Colours::white;
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 0.500f);

		Rectangle<int> thumbnailBounds(x*1.05, y*1.025, width*0.995, height*0.9);

		if (shouldRepaint)
		{	
			g.setColour(Colours::transparentWhite);
			g.fillRect(thumbnailBounds);
			g.setColour(Colour (0xc1ffffff));
			audioDrawObject.drawChannels(g, thumbnailBounds, 0, audioDrawObject.getTotalLength(), 3.0f);
		}
    }
}

void MainComponent::resized()
{
   
}
