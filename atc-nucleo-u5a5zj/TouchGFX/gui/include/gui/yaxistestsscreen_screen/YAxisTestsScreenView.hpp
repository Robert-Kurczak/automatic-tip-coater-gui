#ifndef YAXISTESTSSCREENVIEW_HPP
#define YAXISTESTSSCREENVIEW_HPP

#include <gui_generated/yaxistestsscreen_screen/YAxisTestsScreenViewBase.hpp>
#include <gui/yaxistestsscreen_screen/YAxisTestsScreenPresenter.hpp>

class YAxisTestsScreenView : public YAxisTestsScreenViewBase
{
public:
    YAxisTestsScreenView();
    virtual ~YAxisTestsScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

protected:
    virtual void startTest() override;
    virtual void cancelTest() override;
};

#endif // YAXISTESTSSCREENVIEW_HPP
