#ifndef SPINDLETESTSSCREENVIEW_HPP
#define SPINDLETESTSSCREENVIEW_HPP

#include <gui_generated/spindletestsscreen_screen/SpindleTestsScreenViewBase.hpp>
#include <gui/spindletestsscreen_screen/SpindleTestsScreenPresenter.hpp>

class SpindleTestsScreenView : public SpindleTestsScreenViewBase
{
public:
    SpindleTestsScreenView();
    virtual ~SpindleTestsScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SPINDLETESTSSCREENVIEW_HPP
