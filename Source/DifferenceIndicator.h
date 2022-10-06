#pragma once

#include<JuceHeader.h>
#include"Tuner.h"
#include"TransferFunction.h"

class DifferenceIndicator :
	public juce::AnimatedAppComponent
{
public:
	DifferenceIndicator(Tuner*);
	virtual ~DifferenceIndicator() = default;

	void paint(juce::Graphics&) override;
	void update() override;
	void resized() override;



private:
	Tuner* m_tuner;
	TransferFunction m_transfer_function;
};

