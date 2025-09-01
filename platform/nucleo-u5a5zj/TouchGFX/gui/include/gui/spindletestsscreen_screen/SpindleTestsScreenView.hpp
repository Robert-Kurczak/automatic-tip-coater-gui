#ifndef SPINDLETESTSSCREENVIEW_HPP
#define SPINDLETESTSSCREENVIEW_HPP

#include <gui/spindletestsscreen_screen/SpindleTestsScreenPresenter.hpp>
#include <gui_generated/spindletestsscreen_screen/SpindleTestsScreenViewBase.hpp>

class SpindleTestsScreenView : public SpindleTestsScreenViewBase {
public:
    SpindleTestsScreenView();
    virtual ~SpindleTestsScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void resetFooterButtons();
    void showTestResults(ATC::SpindleTestResults results);

protected:
    virtual void startTest() override;
    virtual void cancelTest() override;
};

#endif // SPINDLETESTSSCREENVIEW_HPP
