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
};

#endif // YAXISSTARTSCREENVIEW_HPP
