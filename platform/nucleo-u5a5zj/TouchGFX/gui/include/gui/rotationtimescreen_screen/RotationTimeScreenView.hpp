#ifndef ROTATIONTIMESCREENVIEW_HPP
#define ROTATIONTIMESCREENVIEW_HPP

#include <gui/rotationtimescreen_screen/RotationTimeScreenPresenter.hpp>
#include <gui_generated/rotationtimescreen_screen/RotationTimeScreenViewBase.hpp>

class RotationTimeScreenView : public RotationTimeScreenViewBase {
public:
    RotationTimeScreenView();
    virtual ~RotationTimeScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

protected:
    virtual void increaseButtonPressed() override;
    virtual void decreaseButtonPressed() override;
    virtual void saveButtonPressed() override;

private:
    void updateDisplayedValue();
};

#endif // ROTATIONTIMESCREENVIEW_HPP
