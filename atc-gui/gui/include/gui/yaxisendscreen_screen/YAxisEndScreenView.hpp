#ifndef YAXISENDSCREENVIEW_HPP
#define YAXISENDSCREENVIEW_HPP

#include <gui_generated/yaxisendscreen_screen/YAxisEndScreenViewBase.hpp>
#include <gui/yaxisendscreen_screen/YAxisEndScreenPresenter.hpp>

class YAxisEndScreenView : public YAxisEndScreenViewBase
{
public:
    YAxisEndScreenView();
    virtual ~YAxisEndScreenView() {}
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

#endif // YAXISENDSCREENVIEW_HPP
