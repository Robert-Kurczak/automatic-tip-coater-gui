#include <gui/zaxisstartscreen_screen/ZAxisStartScreenView.hpp>

static uint16_t savedStartPosition = 0;

ZAxisStartScreenView::ZAxisStartScreenView()
{
    startPosition = savedStartPosition;
    axisStartSelector.setDisplayedValue(startPosition);
}

void ZAxisStartScreenView::setupScreen()
{
    ZAxisStartScreenViewBase::setupScreen();
}

void ZAxisStartScreenView::tearDownScreen()
{
    ZAxisStartScreenViewBase::tearDownScreen();
}

void ZAxisStartScreenView::increaseButtonPressed()
{
    if (startPosition <= maxPosition - positionIncrement)
    {
        startPosition += positionIncrement;
        axisStartSelector.setDisplayedValue(startPosition);
    }
}

void ZAxisStartScreenView::decreaseButtonPressed()
{
    if (startPosition >= positionIncrement)
    {
        startPosition -= positionIncrement;
        axisStartSelector.setDisplayedValue(startPosition);
    }
}

void ZAxisStartScreenView::saveButtonPressed()
{
    savedStartPosition = startPosition;
}