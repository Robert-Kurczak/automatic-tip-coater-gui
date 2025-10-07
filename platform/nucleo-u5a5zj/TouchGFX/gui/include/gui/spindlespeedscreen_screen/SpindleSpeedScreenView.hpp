#ifndef SPINDLESPEEDSCREENVIEW_HPP
#define SPINDLESPEEDSCREENVIEW_HPP

#include <gui/spindlespeedscreen_screen/SpindleSpeedScreenPresenter.hpp>
#include <gui_generated/spindlespeedscreen_screen/SpindleSpeedScreenViewBase.hpp>

class SpindleSpeedScreenView : public SpindleSpeedScreenViewBase {
public:
    SpindleSpeedScreenView();
    virtual ~SpindleSpeedScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

protected:
    virtual void resetConfigurator() override;
    virtual void increaseButtonPressed() override;
    virtual void decreaseButtonPressed() override;
    virtual void saveButtonPressed() override;

private:
    void updateDisplayedValue();
};

#endif // SPINDLESPEEDSCREENVIEW_HPP
