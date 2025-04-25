#ifndef ZAXISENDSCREENVIEW_HPP
#define ZAXISENDSCREENVIEW_HPP

#include <gui_generated/zaxisendscreen_screen/ZAxisEndScreenViewBase.hpp>
#include <gui/zaxisendscreen_screen/ZAxisEndScreenPresenter.hpp>

class ZAxisEndScreenView : public ZAxisEndScreenViewBase
{
public:
    ZAxisEndScreenView();
    virtual ~ZAxisEndScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

protected:
    virtual void increaseButtonPressed() override;
    virtual void decreaseButtonPressed() override;
    virtual void saveButtonPressed() override;

private:
    static const uint16_t minPosition = 0;
    static const uint16_t maxPosition = 65000;
    static const uint8_t positionIncrement = 10;

    uint16_t endPosition = 0;
};

#endif // ZAXISENDSCREENVIEW_HPP
