#include <gui/yaxisstartscreen_screen/YAxisStartScreenView.hpp>

static uint16_t savedStartPosition = 0;

YAxisStartScreenView::YAxisStartScreenView()
{
    startPosition = savedStartPosition;
    axisStartSelector.setDisplayedValue(startPosition);
}

void YAxisStartScreenView::setupScreen()
{
    YAxisStartScreenViewBase::setupScreen();
}

void YAxisStartScreenView::tearDownScreen()
{
    YAxisStartScreenViewBase::tearDownScreen();
}

void YAxisStartScreenView::increaseButtonPressed()
{
    if (startPosition <= maxPosition - positionIncrement)
    {
        startPosition += positionIncrement;
        axisStartSelector.setDisplayedValue(startPosition);
    }
}

void YAxisStartScreenView::decreaseButtonPressed()
{
    if (startPosition >= positionIncrement)
    {
        startPosition -= positionIncrement;
        axisStartSelector.setDisplayedValue(startPosition);
    }
}

void YAxisStartScreenView::saveButtonPressed()
{
    savedStartPosition = startPosition;
}