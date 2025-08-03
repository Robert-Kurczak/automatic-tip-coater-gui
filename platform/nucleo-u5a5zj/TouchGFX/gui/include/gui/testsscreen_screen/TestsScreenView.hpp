#ifndef TESTSSCREENVIEW_HPP
#define TESTSSCREENVIEW_HPP

#include <gui_generated/testsscreen_screen/TestsScreenViewBase.hpp>
#include <gui/testsscreen_screen/TestsScreenPresenter.hpp>

class TestsScreenView : public TestsScreenViewBase
{
public:
    TestsScreenView();
    virtual ~TestsScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // TESTSSCREENVIEW_HPP
