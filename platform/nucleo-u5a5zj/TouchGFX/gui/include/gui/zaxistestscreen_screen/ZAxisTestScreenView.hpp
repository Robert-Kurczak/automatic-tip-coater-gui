#ifndef ZAXISTESTSSCREENVIEW_HPP
#define ZAXISTESTSSCREENVIEW_HPP

#include <gui/zaxistestscreen_screen/ZAxisTestScreenPresenter.hpp>
#include <gui_generated/zaxistestscreen_screen/ZAxisTestScreenViewBase.hpp>

class ZAxisTestScreenView : public ZAxisTestScreenViewBase {
public:
    ZAxisTestScreenView();
    virtual ~ZAxisTestScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void resetFooterButtons();
    void showTestResults(ATC::AxisTestResults results);

protected:
    virtual void startTest() override;
    virtual void cancelTest() override;
};

#endif // ZAXISTESTSSCREENVIEW_HPP
