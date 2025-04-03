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
};

#endif // YAXISENDSCREENVIEW_HPP
