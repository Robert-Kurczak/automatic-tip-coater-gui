#ifndef SPINDLEDIRECTIONSCREENVIEW_HPP
#define SPINDLEDIRECTIONSCREENVIEW_HPP

#include <gui_generated/spindledirectionscreen_screen/SpindleDirectionScreenViewBase.hpp>
#include <gui/spindledirectionscreen_screen/SpindleDirectionScreenPresenter.hpp>

class SpindleDirectionScreenView : public SpindleDirectionScreenViewBase
{
public:
    SpindleDirectionScreenView();
    virtual ~SpindleDirectionScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SPINDLEDIRECTIONSCREENVIEW_HPP
