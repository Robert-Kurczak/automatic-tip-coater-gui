#ifndef YAXISSPEEDSCREENVIEW_HPP
#define YAXISSPEEDSCREENVIEW_HPP

#include <gui_generated/yaxisspeedscreen_screen/YAxisSpeedScreenViewBase.hpp>
#include <gui/yaxisspeedscreen_screen/YAxisSpeedScreenPresenter.hpp>

class YAxisSpeedScreenView : public YAxisSpeedScreenViewBase
{
public:
    YAxisSpeedScreenView();
    virtual ~YAxisSpeedScreenView() {}
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

#endif // YAXISSPEEDSCREENVIEW_HPP
