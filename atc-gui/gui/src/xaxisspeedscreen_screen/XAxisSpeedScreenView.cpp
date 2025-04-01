#include <gui/xaxisspeedscreen_screen/XAxisSpeedScreenView.hpp>

static uint8_t savedSpeed = 0;

XAxisSpeedScreenView::XAxisSpeedScreenView()
{
    speed = savedSpeed;
    xAxisSpeedSelector.setDisplayedValue(savedSpeed);
}

void XAxisSpeedScreenView::setupScreen()
{
    XAxisSpeedScreenViewBase::setupScreen();
}

void XAxisSpeedScreenView::tearDownScreen()
{
    XAxisSpeedScreenViewBase::tearDownScreen();
}

void XAxisSpeedScreenView::increaseButtonPressed()
{
    if (speed <= maxSpeed - speedIncrement)
    {
        speed += speedIncrement;
        xAxisSpeedSelector.setDisplayedValue(speed);
    }
}

void XAxisSpeedScreenView::decreaseButtonPressed()
{
    if (speed >= speedIncrement)
    {
        speed -= speedIncrement;
        xAxisSpeedSelector.setDisplayedValue(speed);
    }
}

void XAxisSpeedScreenView::saveButtonPressed()
{
    savedSpeed = speed;
}