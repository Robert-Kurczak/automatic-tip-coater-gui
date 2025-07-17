#ifndef XAXISENDSCREENVIEW_HPP
#define XAXISENDSCREENVIEW_HPP

#include <gui_generated/xaxisendscreen_screen/XAxisEndScreenViewBase.hpp>
#include <gui/xaxisendscreen_screen/XAxisEndScreenPresenter.hpp>

class XAxisEndScreenView : public XAxisEndScreenViewBase
{
public:
    XAxisEndScreenView();
    virtual ~XAxisEndScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

protected:
    virtual void increaseButtonPressed() override;
    virtual void decreaseButtonPressed() override;
    virtual void saveButtonPressed() override;

private:
    void updateDisplayedValue();
};

#endif // XAXISENDSCREENVIEW_HPP
