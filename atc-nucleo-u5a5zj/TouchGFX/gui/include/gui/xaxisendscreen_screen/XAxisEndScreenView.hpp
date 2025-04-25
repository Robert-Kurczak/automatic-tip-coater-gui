#ifndef XAXISENDSCREENVIEW_HPP
#define XAXISENDSCREENVIEW_HPP

#include <gui_generated/xaxisendscreen_screen/XAxisEndScreenViewBase.hpp>
#include <gui/xaxisendscreen_screen/XAxisEndScreenPresenter.hpp>

class XAxisEndScreenView : public XAxisEndScreenViewBase
{
public:
    XAxisEndScreenView();
    virtual ~XAxisEndScreenView() {}
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

#endif // XAXISENDSCREENVIEW_HPP
