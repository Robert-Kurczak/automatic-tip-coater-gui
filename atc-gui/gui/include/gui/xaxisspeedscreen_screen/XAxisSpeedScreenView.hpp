#ifndef XAXISSPEEDSCREENVIEW_HPP
#define XAXISSPEEDSCREENVIEW_HPP

#include <gui_generated/xaxisspeedscreen_screen/XAxisSpeedScreenViewBase.hpp>
#include <gui/xaxisspeedscreen_screen/XAxisSpeedScreenPresenter.hpp>

class XAxisSpeedScreenView : public XAxisSpeedScreenViewBase
{
public:
    XAxisSpeedScreenView();
    virtual ~XAxisSpeedScreenView() {}
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

#endif // XAXISSPEEDSCREENVIEW_HPP
