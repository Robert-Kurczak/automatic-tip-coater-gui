#include <gui/zaxisspeedscreen_screen/ZAxisSpeedScreenView.hpp>

static uint8_t savedSpeed = 0;

ZAxisSpeedScreenView::ZAxisSpeedScreenView()
{
    speed = savedSpeed;
    axisSpeedSelector.setDisplayedValue(savedSpeed);
}

void ZAxisSpeedScreenView::setupScreen()
{
    ZAxisSpeedScreenViewBase::setupScreen();
}

void ZAxisSpeedScreenView::tearDownScreen()
{
    ZAxisSpeedScreenViewBase::tearDownScreen();
}

void ZAxisSpeedScreenView::increaseButtonPressed()
{
    if (speed <= maxSpeed - speedIncrement)
    {
        speed += speedIncrement;
        axisSpeedSelector.setDisplayedValue(speed);
    }
}

void ZAxisSpeedScreenView::decreaseButtonPressed()
{
    if (speed >= speedIncrement)
    {
        speed -= speedIncrement;
        axisSpeedSelector.setDisplayedValue(speed);
    }
}

void ZAxisSpeedScreenView::saveButtonPressed()
{
    savedSpeed = speed;
}