#ifndef YAXISSTARTSCREENVIEW_HPP
#define YAXISSTARTSCREENVIEW_HPP

#include <gui_generated/yaxisstartscreen_screen/YAxisStartScreenViewBase.hpp>
#include <gui/yaxisstartscreen_screen/YAxisStartScreenPresenter.hpp>

class YAxisStartScreenView : public YAxisStartScreenViewBase
{
public:
    YAxisStartScreenView();
    virtual ~YAxisStartScreenView() {}
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

#endif // YAXISSTARTSCREENVIEW_HPP
