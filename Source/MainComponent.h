#pragma once
#include <JuceHeader.h>


//==============================================================================
/*
 * Can load, edit, and save a .txt file
 */
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    juce::TextEditor mEditor;
    juce::TextButton mLoadButton, mSaveButton;

    std::unique_ptr<juce::FileChooser> mLoader, mSaver;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
