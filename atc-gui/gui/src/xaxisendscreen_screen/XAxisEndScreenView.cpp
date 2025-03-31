#include <gui/xaxisendscreen_screen/XAxisEndScreenView.hpp>

static uint16_t savedEndPosition = 0;

XAxisEndScreenView::XAxisEndScreenView()
{
    endPosition = savedEndPosition;
    xAxisEndSelector.setDisplayedValue(savedEndPosition);
}

void XAxisEndScreenView::setupScreen()
{
    XAxisEndScreenViewBase::setupScreen();
}

void XAxisEndScreenView::tearDownScreen()
{
    XAxisEndScreenViewBase::tearDownScreen();
}

void XAxisEndScreenView::increaseButtonPressed()
{
    if (endPosition <= maxPosition - positionIncrement)
    {
        endPosition += positionIncrement;
        xAxisEndSelector.setDisplayedValue(endPosition);
    }
}

void XAxisEndScreenView::decreaseButtonPressed()
{
    if (endPosition >= positionIncrement)
    {
        endPosition -= positionIncrement;
        xAxisEndSelector.setDisplayedValue(endPosition);
    }
}

void XAxisEndScreenView::saveButtonPressed()
{
    savedEndPosition = endPosition;
}