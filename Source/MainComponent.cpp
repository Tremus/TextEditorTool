#include "MainComponent.h"


//==============================================================================
MainComponent::MainComponent()
    : mLoadButton("Load", "Load a text file")
    , mSaveButton("Save", "Save text to file")
{
    mEditor.setColour(juce::Label::ColourIds::backgroundColourId, juce::Colours::whitesmoke);
    mEditor.setColour(juce::Label::ColourIds::textColourId, juce::Colours::black);
    mEditor.setColour(juce::Label::ColourIds::textWhenEditingColourId, juce::Colours::black);
    mEditor.setMultiLine(true, true);
    mEditor.setReturnKeyStartsNewLine (true);

    mEditor.setText("Press load to load a .txt file.\nPress save to write text to the screen.", juce::dontSendNotification);

    mLoader = std::make_unique<juce::FileChooser> ("Open", juce::File::getSpecialLocation (juce::File::userDesktopDirectory), "*.txt");
    mSaver  = std::make_unique<juce::FileChooser> ("Save", juce::File::getSpecialLocation (juce::File::userDesktopDirectory), "*.txt");

    mLoadButton.onClick = [&]()
    {
        auto callback = [&] (const juce::FileChooser& chooser)
        {
            auto file = chooser.getResult();
            if (file.exists())
                mEditor.setText(file.loadFileAsString(), juce::sendNotificationSync);
        };
        mLoader->launchAsync (juce::FileBrowserComponent::openMode, callback);
    };

    mSaveButton.onClick = [&]()
    {
        auto callback = [&] (const juce::FileChooser& chooser)
        {
            auto file = chooser.getResult();
            if (file.exists())
                file.create();
            file.replaceWithText(mEditor.getText());
        };
        mSaver->launchAsync (juce::FileBrowserComponent::saveMode, callback);
    };

    addAndMakeVisible(mLoadButton);
    addAndMakeVisible(mSaveButton);
    addAndMakeVisible(mEditor);

    setSize (600, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
}

void MainComponent::resized()
{
    mLoadButton.setBounds(10, 10, 80, 30);
    mSaveButton.setBounds(10, 50, 80, 30);
    mEditor.setBounds(100, 10, 490, 380);
}
