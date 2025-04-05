#ifndef ROTATIONSPEEDSCREENVIEW_HPP
#define ROTATIONSPEEDSCREENVIEW_HPP

#include <gui_generated/rotationspeedscreen_screen/RotationSpeedScreenViewBase.hpp>
#include <gui/rotationspeedscreen_screen/RotationSpeedScreenPresenter.hpp>

class RotationSpeedScreenView : public RotationSpeedScreenViewBase
{
public:
    RotationSpeedScreenView();
    virtual ~RotationSpeedScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

protected:
    virtual void increaseButtonPressed() override;
    virtual void decreaseButtonPressed() override;
    virtual void saveButtonPressed() override;

private:
    static const uint8_t minSpeed = 0;
    static const uint8_t maxSpeed = 255;
    static const uint8_t speedIncrement = 1;

    uint16_t speed = 0;
};

#endif // ROTATIONSPEEDSCREENVIEW_HPP
