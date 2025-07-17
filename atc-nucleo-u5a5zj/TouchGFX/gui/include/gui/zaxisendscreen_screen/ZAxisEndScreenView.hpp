#ifndef ZAXISENDSCREENVIEW_HPP
#define ZAXISENDSCREENVIEW_HPP

#include <gui/zaxisendscreen_screen/ZAxisEndScreenPresenter.hpp>
#include <gui_generated/zaxisendscreen_screen/ZAxisEndScreenViewBase.hpp>

class ZAxisEndScreenView : public ZAxisEndScreenViewBase {
public:
    ZAxisEndScreenView();
    virtual ~ZAxisEndScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

protected:
    virtual void increaseButtonPressed() override;
    virtual void decreaseButtonPressed() override;
    virtual void saveButtonPressed() override;

private:
    void updateDisplayedValue();
};

#endif // ZAXISENDSCREENVIEW_HPP
