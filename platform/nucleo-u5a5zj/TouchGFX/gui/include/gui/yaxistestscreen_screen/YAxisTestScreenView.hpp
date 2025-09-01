#ifndef YAXISTESTSSCREENVIEW_HPP
#define YAXISTESTSSCREENVIEW_HPP

#include "application/System/Tasks/Task/AxisTestTask/AxisTestResults.hpp"

#include <gui/yaxistestscreen_screen/YAxisTestScreenPresenter.hpp>
#include <gui_generated/yaxistestscreen_screen/YAxisTestScreenViewBase.hpp>

class YAxisTestScreenView : public YAxisTestScreenViewBase {
public:
    YAxisTestScreenView();
    virtual ~YAxisTestScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void resetFooterButtons();
    void showTestResults(ATC::AxisTestResults results);

protected:
    virtual void startTest() override;
    virtual void cancelTest() override;
};

#endif // YAXISTESTSSCREENVIEW_HPP
