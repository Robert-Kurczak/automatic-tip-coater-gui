#ifndef SPINDLETESTSSCREENVIEW_HPP
#define SPINDLETESTSSCREENVIEW_HPP

#include <gui/spindletestscreen_screen/SpindleTestScreenPresenter.hpp>
#include <gui_generated/spindletestscreen_screen/SpindleTestScreenViewBase.hpp>

class SpindleTestScreenView : public SpindleTestScreenViewBase {
public:
    SpindleTestScreenView();
    virtual ~SpindleTestScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void resetFooterButtons();
    void showTestResults(ATC::SpindleTestResults results);

protected:
    virtual void startTest() override;
    virtual void cancelTest() override;
};

#endif // SPINDLETESTSSCREENVIEW_HPP
