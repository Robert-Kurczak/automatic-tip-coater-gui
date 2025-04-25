#include <gui/yaxisspeedscreen_screen/YAxisSpeedScreenView.hpp>

static uint8_t savedSpeed = 0;

YAxisSpeedScreenView::YAxisSpeedScreenView()
{
    speed = savedSpeed;
    axisSpeedSelector.setDisplayedValue(savedSpeed);
}

void YAxisSpeedScreenView::setupScreen()
{
    YAxisSpeedScreenViewBase::setupScreen();
}

void YAxisSpeedScreenView::tearDownScreen()
{
    YAxisSpeedScreenViewBase::tearDownScreen();
}


void YAxisSpeedScreenView::increaseButtonPressed()
{
    if (speed <= maxSpeed - speedIncrement)
    {
        speed += speedIncrement;
        axisSpeedSelector.setDisplayedValue(speed);
    }
}

void YAxisSpeedScreenView::decreaseButtonPressed()
{
    if (speed >= speedIncrement)
    {
        speed -= speedIncrement;
        axisSpeedSelector.setDisplayedValue(speed);
    }
}

void YAxisSpeedScreenView::saveButtonPressed()
{
    savedSpeed = speed;
}