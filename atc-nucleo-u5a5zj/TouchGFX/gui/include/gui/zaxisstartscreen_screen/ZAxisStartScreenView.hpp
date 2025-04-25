#ifndef ZAXISSTARTSCREENVIEW_HPP
#define ZAXISSTARTSCREENVIEW_HPP

#include <gui_generated/zaxisstartscreen_screen/ZAxisStartScreenViewBase.hpp>
#include <gui/zaxisstartscreen_screen/ZAxisStartScreenPresenter.hpp>

class ZAxisStartScreenView : public ZAxisStartScreenViewBase
{
public:
    ZAxisStartScreenView();
    virtual ~ZAxisStartScreenView() {}
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

#endif // ZAXISSTARTSCREENVIEW_HPP
