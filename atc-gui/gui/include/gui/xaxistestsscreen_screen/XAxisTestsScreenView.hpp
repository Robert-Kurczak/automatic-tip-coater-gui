#ifndef XAXISTESTSSCREENVIEW_HPP
#define XAXISTESTSSCREENVIEW_HPP

#include <gui_generated/xaxistestsscreen_screen/XAxisTestsScreenViewBase.hpp>
#include <gui/xaxistestsscreen_screen/XAxisTestsScreenPresenter.hpp>

class XAxisTestsScreenView : public XAxisTestsScreenViewBase
{
public:
    XAxisTestsScreenView();
    virtual ~XAxisTestsScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

protected:
    virtual void startTest() override;
    virtual void cancelTest() override;
};

#endif // XAXISTESTSSCREENVIEW_HPP
