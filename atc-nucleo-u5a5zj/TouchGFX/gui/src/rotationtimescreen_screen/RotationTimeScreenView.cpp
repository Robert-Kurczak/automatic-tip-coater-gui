#include <gui/rotationtimescreen_screen/RotationTimeScreenView.hpp>

static uint16_t savedTimeMs = 0;

RotationTimeScreenView::RotationTimeScreenView()
{
    timeMs = savedTimeMs;
    timeSelector.setDisplayedValue(savedTimeMs);
}

void RotationTimeScreenView::setupScreen()
{
    RotationTimeScreenViewBase::setupScreen();
}

void RotationTimeScreenView::tearDownScreen()
{
    RotationTimeScreenViewBase::tearDownScreen();
}

void RotationTimeScreenView::increaseButtonPressed()
{
    if (timeMs <= maxTimeMs - timeIncrement)
    {
        timeMs += timeIncrement;
        timeSelector.setDisplayedValue(timeMs);
    }
}

void RotationTimeScreenView::decreaseButtonPressed()
{
    if (timeMs >= timeIncrement)
    {
        timeMs -= timeIncrement;
        timeSelector.setDisplayedValue(timeMs);
    }
}

void RotationTimeScreenView::saveButtonPressed()
{
    savedTimeMs = timeMs;
}