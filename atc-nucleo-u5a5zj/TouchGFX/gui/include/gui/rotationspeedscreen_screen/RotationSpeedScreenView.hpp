#ifndef ROTATIONSPEEDSCREENVIEW_HPP
#define ROTATIONSPEEDSCREENVIEW_HPP

#include <gui_generated/rotationspeedscreen_screen/RotationSpeedScreenViewBase.hpp>
#include <gui/rotationspeedscreen_screen/RotationSpeedScreenPresenter.hpp>

class RotationSpeedScreenView : public RotationSpeedScreenViewBase
{
public:
    RotationSpeedScreenView();
    virtual ~RotationSpeedScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

protected:
    virtual void increaseButtonPressed() override;
    virtual void decreaseButtonPressed() override;
    virtual void saveButtonPressed() override;

private:
    void updateDisplayedValue();
};

#endif // ROTATIONSPEEDSCREENVIEW_HPP
