#include <gui/yaxisendscreen_screen/YAxisEndScreenView.hpp>

static uint16_t savedEndPosition = 0;

YAxisEndScreenView::YAxisEndScreenView()
{
    endPosition = savedEndPosition;
    axisEndSelector.setDisplayedValue(savedEndPosition);
}

void YAxisEndScreenView::setupScreen()
{
    YAxisEndScreenViewBase::setupScreen();
}

void YAxisEndScreenView::tearDownScreen()
{
    YAxisEndScreenViewBase::tearDownScreen();
}


void YAxisEndScreenView::increaseButtonPressed()
{
    if (endPosition <= maxPosition - positionIncrement)
    {
        endPosition += positionIncrement;
        axisEndSelector.setDisplayedValue(endPosition);
    }
}

void YAxisEndScreenView::decreaseButtonPressed()
{
    if (endPosition >= positionIncrement)
    {
        endPosition -= positionIncrement;
        axisEndSelector.setDisplayedValue(endPosition);
    }
}

void YAxisEndScreenView::saveButtonPressed()
{
    savedEndPosition = endPosition;
}