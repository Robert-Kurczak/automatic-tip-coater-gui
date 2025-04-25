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
    virtual void increaseButtonPressed() override;
    virtual void decreaseButtonPressed() override;
    virtual void saveButtonPressed() override;

private:
    static const uint16_t minPosition = 0;
    static const uint16_t maxPosition = 65000;
    static const uint8_t positionIncrement = 10;

    uint16_t startPosition = 0;
};

#endif // XAXISSTARTSCREENVIEW_HPP
