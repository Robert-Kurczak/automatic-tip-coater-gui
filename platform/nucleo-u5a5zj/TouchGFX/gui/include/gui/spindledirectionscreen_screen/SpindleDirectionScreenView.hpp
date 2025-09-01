#ifndef SPINDLEDIRECTIONSCREENVIEW_HPP
#define SPINDLEDIRECTIONSCREENVIEW_HPP

#include <gui/spindledirectionscreen_screen/SpindleDirectionScreenPresenter.hpp>
#include <gui_generated/spindledirectionscreen_screen/SpindleDirectionScreenViewBase.hpp>

class SpindleDirectionScreenView : public SpindleDirectionScreenViewBase {
public:
    SpindleDirectionScreenView();
    virtual ~SpindleDirectionScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

protected:
    virtual void clockwiseButtonPressed() override;
    virtual void counterClockwiseButtonPressed() override;
    virtual void saveButtonPressed() override;

private:
    void updateDisplayedValue();
};

#endif // SPINDLEDIRECTIONSCREENVIEW_HPP
