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
};

#endif // YAXISSPEEDSCREENVIEW_HPP
