#ifndef STARTSCREENVIEW_HPP
#define STARTSCREENVIEW_HPP

#include <gui/startscreen_screen/StartScreenPresenter.hpp>
#include <gui_generated/startscreen_screen/StartScreenViewBase.hpp>


class StartScreenView : public StartScreenViewBase {
private:
    void displaySettings();

public:
    StartScreenView();
    virtual ~StartScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void startCoating() override;
    virtual void cancelCoating() override;

    void resetFooterButtons();
};

#endif // STARTSCREENVIEW_HPP
