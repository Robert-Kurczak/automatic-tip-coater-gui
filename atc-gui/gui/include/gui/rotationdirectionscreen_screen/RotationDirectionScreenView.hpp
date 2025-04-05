#ifndef ROTATIONDIRECTIONSCREENVIEW_HPP
#define ROTATIONDIRECTIONSCREENVIEW_HPP

#include <gui_generated/rotationdirectionscreen_screen/RotationDirectionScreenViewBase.hpp>
#include <gui/rotationdirectionscreen_screen/RotationDirectionScreenPresenter.hpp>

class RotationDirectionScreenView : public RotationDirectionScreenViewBase
{
public:
    RotationDirectionScreenView();
    virtual ~RotationDirectionScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

protected:
    virtual void clockwiseButtonPressed() override;
    virtual void counterClockwiseButtonPressed() override;
    virtual void saveButtonPressed() override;

private:
    bool clockwise = true;
};

#endif // ROTATIONDIRECTIONSCREENVIEW_HPP
