#include <gui/rotationspeedscreen_screen/RotationSpeedScreenView.hpp>

static uint8_t savedSpeed = 0;

RotationSpeedScreenView::RotationSpeedScreenView()
{
    speed = savedSpeed;
    speedSelector.setDisplayedValue(savedSpeed);
}

void RotationSpeedScreenView::setupScreen()
{
    RotationSpeedScreenViewBase::setupScreen();
}

void RotationSpeedScreenView::tearDownScreen()
{
    RotationSpeedScreenViewBase::tearDownScreen();
}

void RotationSpeedScreenView::increaseButtonPressed()
{
    if (speed <= maxSpeed - speedIncrement)
    {
        speed += speedIncrement;
        speedSelector.setDisplayedValue(speed);
    }
}

void RotationSpeedScreenView::decreaseButtonPressed()
{
    if (speed >= speedIncrement)
    {
        speed -= speedIncrement;
        speedSelector.setDisplayedValue(speed);
    }
}

void RotationSpeedScreenView::saveButtonPressed()
{
    savedSpeed = speed;
}