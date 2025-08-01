#ifndef XAXISTESTSSCREENVIEW_HPP
#define XAXISTESTSSCREENVIEW_HPP

#include "application/Hardware/Axes/AxisTestResults.hpp"

#include <gui/xaxistestsscreen_screen/XAxisTestsScreenPresenter.hpp>
#include <gui_generated/xaxistestsscreen_screen/XAxisTestsScreenViewBase.hpp>

class XAxisTestsScreenView : public XAxisTestsScreenViewBase {
public:
    XAxisTestsScreenView();
    virtual ~XAxisTestsScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void resetFooterButtons();
    void showTestResults(ATC::AxisTestResults results);

protected:
    virtual void startTest() override;
    virtual void cancelTest() override;
};

#endif // XAXISTESTSSCREENVIEW_HPP
