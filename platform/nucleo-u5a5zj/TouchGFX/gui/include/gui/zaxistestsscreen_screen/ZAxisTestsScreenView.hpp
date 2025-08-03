#ifndef ZAXISTESTSSCREENVIEW_HPP
#define ZAXISTESTSSCREENVIEW_HPP

#include <gui/zaxistestsscreen_screen/ZAxisTestsScreenPresenter.hpp>
#include <gui_generated/zaxistestsscreen_screen/ZAxisTestsScreenViewBase.hpp>

class ZAxisTestsScreenView : public ZAxisTestsScreenViewBase {
public:
    ZAxisTestsScreenView();
    virtual ~ZAxisTestsScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void resetFooterButtons();
    void showTestResults(ATC::AxisTestResults results);

protected:
    virtual void startTest() override;
    virtual void cancelTest() override;
};

#endif // ZAXISTESTSSCREENVIEW_HPP
