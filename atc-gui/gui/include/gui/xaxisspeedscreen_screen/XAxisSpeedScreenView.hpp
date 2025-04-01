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
};

#endif // XAXISSPEEDSCREENVIEW_HPP
