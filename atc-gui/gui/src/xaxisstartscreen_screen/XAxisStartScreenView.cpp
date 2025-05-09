#include <gui/xaxisstartscreen_screen/XAxisStartScreenView.hpp>

static uint16_t savedStartPosition = 0;

XAxisStartScreenView::XAxisStartScreenView()
{
    startPosition = savedStartPosition;
    axisStartSelector.setDisplayedValue(startPosition);
}

void XAxisStartScreenView::setupScreen()
{
    XAxisStartScreenViewBase::setupScreen();
}

void XAxisStartScreenView::tearDownScreen()
{
    XAxisStartScreenViewBase::tearDownScreen();
}

void XAxisStartScreenView::increaseButtonPressed()
{
    if (startPosition <= maxPosition - positionIncrement)
    {
        startPosition += positionIncrement;
        axisStartSelector.setDisplayedValue(startPosition);
    }
}

void XAxisStartScreenView::decreaseButtonPressed()
{
    if (startPosition >= positionIncrement)
    {
        startPosition -= positionIncrement;
        axisStartSelector.setDisplayedValue(startPosition);
    }
}

void XAxisStartScreenView::saveButtonPressed()
{
    savedStartPosition = startPosition;
}