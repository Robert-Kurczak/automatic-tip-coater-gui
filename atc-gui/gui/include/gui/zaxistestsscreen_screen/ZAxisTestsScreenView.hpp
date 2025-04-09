#ifndef ZAXISTESTSSCREENVIEW_HPP
#define ZAXISTESTSSCREENVIEW_HPP

#include <gui_generated/zaxistestsscreen_screen/ZAxisTestsScreenViewBase.hpp>
#include <gui/zaxistestsscreen_screen/ZAxisTestsScreenPresenter.hpp>

class ZAxisTestsScreenView : public ZAxisTestsScreenViewBase
{
public:
    ZAxisTestsScreenView();
    virtual ~ZAxisTestsScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

protected:
    virtual void startTest() override;
    virtual void cancelTest() override;
};

#endif // ZAXISTESTSSCREENVIEW_HPP
