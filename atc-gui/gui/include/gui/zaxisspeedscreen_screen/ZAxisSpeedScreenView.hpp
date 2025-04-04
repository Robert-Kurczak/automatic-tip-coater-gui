#ifndef ZAXISSPEEDSCREENVIEW_HPP
#define ZAXISSPEEDSCREENVIEW_HPP

#include <gui_generated/zaxisspeedscreen_screen/ZAxisSpeedScreenViewBase.hpp>
#include <gui/zaxisspeedscreen_screen/ZAxisSpeedScreenPresenter.hpp>

class ZAxisSpeedScreenView : public ZAxisSpeedScreenViewBase
{
public:
    ZAxisSpeedScreenView();
    virtual ~ZAxisSpeedScreenView() {}
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

#endif // ZAXISSPEEDSCREENVIEW_HPP
