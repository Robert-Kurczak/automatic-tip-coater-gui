#ifndef HEATERTESTSSCREENVIEW_HPP
#define HEATERTESTSSCREENVIEW_HPP

#include <gui_generated/heatertestsscreen_screen/HeaterTestsScreenViewBase.hpp>
#include <gui/heatertestsscreen_screen/HeaterTestsScreenPresenter.hpp>

class HeaterTestsScreenView : public HeaterTestsScreenViewBase
{
public:
    HeaterTestsScreenView();
    virtual ~HeaterTestsScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

protected:
    virtual void startTest() override;
    virtual void cancelTest() override;
};

#endif // HEATERTESTSSCREENVIEW_HPP
