#ifndef SPINDLESPEEDSCREENVIEW_HPP
#define SPINDLESPEEDSCREENVIEW_HPP

#include <gui_generated/spindlespeedscreen_screen/SpindleSpeedScreenViewBase.hpp>
#include <gui/spindlespeedscreen_screen/SpindleSpeedScreenPresenter.hpp>

class SpindleSpeedScreenView : public SpindleSpeedScreenViewBase
{
public:
    SpindleSpeedScreenView();
    virtual ~SpindleSpeedScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SPINDLESPEEDSCREENVIEW_HPP
