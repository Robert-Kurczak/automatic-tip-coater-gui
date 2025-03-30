#ifndef XAXISSTARTSCREENVIEW_HPP
#define XAXISSTARTSCREENVIEW_HPP

#include <gui_generated/xaxisstartscreen_screen/XAxisStartScreenViewBase.hpp>
#include <gui/xaxisstartscreen_screen/XAxisStartScreenPresenter.hpp>

class XAxisStartScreenView : public XAxisStartScreenViewBase
{
public:
    XAxisStartScreenView();
    virtual ~XAxisStartScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

protected:
    virtual void increaseStartPositionPressed() override;
    virtual void decreaseStartPositionPressed() override;
    virtual void applyStartPositionPressed() override;

private:
    static const uint16_t minPosition = 0;
    static const uint16_t maxPosition = 65000;
    static const uint8_t positionIncrement = 10;

    static const uint8_t minSpeed = 0;
    static const uint8_t maxSpeed = 255;
    static const uint8_t speedIncrement = 1;

    uint16_t startPosition = 0;
    uint16_t endPosition = 0;
    uint16_t speed = 0;

    void updateStartPositionValue();
};

#endif // XAXISSTARTSCREENVIEW_HPP
