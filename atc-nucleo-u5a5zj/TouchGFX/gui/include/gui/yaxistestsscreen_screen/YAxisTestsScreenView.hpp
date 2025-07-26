#ifndef YAXISTESTSSCREENVIEW_HPP
#define YAXISTESTSSCREENVIEW_HPP

#include "application/Hardware/Axes/AxisTestResults.hpp"

#include <gui/yaxistestsscreen_screen/YAxisTestsScreenPresenter.hpp>
#include <gui_generated/yaxistestsscreen_screen/YAxisTestsScreenViewBase.hpp>

class YAxisTestsScreenView : public YAxisTestsScreenViewBase {
public:
    YAxisTestsScreenView();
    virtual ~YAxisTestsScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void showTestResults(ATC::AxisTestResults results);

protected:
    virtual void startTest() override;
    virtual void cancelTest() override;
};

#endif // YAXISTESTSSCREENVIEW_HPP
