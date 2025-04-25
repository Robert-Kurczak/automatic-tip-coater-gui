#include <gui/zaxisendscreen_screen/ZAxisEndScreenView.hpp>

static uint16_t savedEndPosition = 0;

ZAxisEndScreenView::ZAxisEndScreenView()
{
    endPosition = savedEndPosition;
    axisEndSelector.setDisplayedValue(savedEndPosition);
}

void ZAxisEndScreenView::setupScreen()
{
    ZAxisEndScreenViewBase::setupScreen();
}

void ZAxisEndScreenView::tearDownScreen()
{
    ZAxisEndScreenViewBase::tearDownScreen();
}

void ZAxisEndScreenView::increaseButtonPressed()
{
    if (endPosition <= maxPosition - positionIncrement)
    {
        endPosition += positionIncrement;
        axisEndSelector.setDisplayedValue(endPosition);
    }
}

void ZAxisEndScreenView::decreaseButtonPressed()
{
    if (endPosition >= positionIncrement)
    {
        endPosition -= positionIncrement;
        axisEndSelector.setDisplayedValue(endPosition);
    }
}

void ZAxisEndScreenView::saveButtonPressed()
{
    savedEndPosition = endPosition;
}