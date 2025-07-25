#ifndef XAXISTESTSSCREENVIEW_HPP
#define XAXISTESTSSCREENVIEW_HPP

#include "application/Axes/XAxis/XAxisTestResults.hpp"

#include <gui/xaxistestsscreen_screen/XAxisTestsScreenPresenter.hpp>
#include <gui_generated/xaxistestsscreen_screen/XAxisTestsScreenViewBase.hpp>

class XAxisTestsScreenView : public XAxisTestsScreenViewBase {
public:
    XAxisTestsScreenView();
    virtual ~XAxisTestsScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void showTestResults(ATC::XAxisTestResults results);

protected:
    virtual void startTest() override;
    virtual void cancelTest() override;
};

#endif // XAXISTESTSSCREENVIEW_HPP
