#ifndef XAXISSTARTSCREENVIEW_HPP
#define XAXISSTARTSCREENVIEW_HPP

#include <gui_generated/xaxisstartscreen_screen/XAxisStartScreenViewBase.hpp>
#include <gui/xaxisstartscreen_screen/XAxisStartScreenPresenter.hpp>

class XAxisStartScreenView : public XAxisStartScreenViewBase
{
public:
    XAxisStartScreenView();
    virtual ~XAxisStartScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

protected:
    virtual void increaseButtonPressed() override;
    virtual void decreaseButtonPressed() override;
    virtual void saveButtonPressed() override;

private:
    void updateDisplayedValue();
};

#endif // XAXISSTARTSCREENVIEW_HPP
