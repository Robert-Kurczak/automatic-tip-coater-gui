#ifndef ROTATIONTESTSSCREENVIEW_HPP
#define ROTATIONTESTSSCREENVIEW_HPP

#include <gui_generated/rotationtestsscreen_screen/RotationTestsScreenViewBase.hpp>
#include <gui/rotationtestsscreen_screen/RotationTestsScreenPresenter.hpp>

class RotationTestsScreenView : public RotationTestsScreenViewBase
{
public:
    RotationTestsScreenView();
    virtual ~RotationTestsScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void showTestResults(ATC::RotatorTestResults results);

protected:
    virtual void startTest() override;
    virtual void cancelTest() override;
};

#endif // ROTATIONTESTSSCREENVIEW_HPP
