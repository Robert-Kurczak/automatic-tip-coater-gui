#ifndef XAXISTESTSSCREENVIEW_HPP
#define XAXISTESTSSCREENVIEW_HPP

#include "application/System/Tasks/Task/AxisTestTask/AxisTestResults.hpp"

#include <gui/xaxistestscreen_screen/XAxisTestScreenPresenter.hpp>
#include <gui_generated/xaxistestscreen_screen/XAxisTestScreenViewBase.hpp>

class XAxisTestScreenView : public XAxisTestScreenViewBase {
public:
    XAxisTestScreenView();
    virtual ~XAxisTestScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void resetFooterButtons();
    void showTestResults(ATC::AxisTestResults results);

protected:
    virtual void startTest() override;
    virtual void cancelTest() override;
};

#endif // XAXISTESTSSCREENVIEW_HPP
