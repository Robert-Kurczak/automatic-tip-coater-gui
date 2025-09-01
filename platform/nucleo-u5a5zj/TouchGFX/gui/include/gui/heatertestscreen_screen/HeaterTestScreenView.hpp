#ifndef HEATERTESTSSCREENVIEW_HPP
#define HEATERTESTSSCREENVIEW_HPP

#include "application/System/Tasks/Task/HeaterTestTask/HeaterTestResults.hpp"

#include <gui/heatertestscreen_screen/HeaterTestScreenPresenter.hpp>
#include <gui_generated/heatertestscreen_screen/HeaterTestScreenViewBase.hpp>

class HeaterTestScreenView : public HeaterTestScreenViewBase {
public:
    HeaterTestScreenView();
    virtual ~HeaterTestScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void resetFooterButtons();
    void showTestResults(ATC::HeaterTestResults results);

protected:
    virtual void startTest() override;
    virtual void cancelTest() override;
};

#endif // HEATERTESTSSCREENVIEW_HPP
