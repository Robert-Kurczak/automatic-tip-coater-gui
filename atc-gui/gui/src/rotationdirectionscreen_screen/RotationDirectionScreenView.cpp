#include <gui/rotationdirectionscreen_screen/RotationDirectionScreenView.hpp>

static bool savedClockwise = true;

RotationDirectionScreenView::RotationDirectionScreenView()
{
    clockwise = savedClockwise;

    rotationDirectionSelector.setClockwiseState(clockwise);
}

void RotationDirectionScreenView::setupScreen()
{
    RotationDirectionScreenViewBase::setupScreen();
}

void RotationDirectionScreenView::tearDownScreen()
{
    RotationDirectionScreenViewBase::tearDownScreen();
}

void RotationDirectionScreenView::clockwiseButtonPressed()
{
    clockwise = false;
}

void RotationDirectionScreenView::counterClockwiseButtonPressed()
{
    clockwise = true;
}

void RotationDirectionScreenView::saveButtonPressed()
{
    savedClockwise = clockwise;
}