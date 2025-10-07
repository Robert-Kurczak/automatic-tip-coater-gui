#ifndef SPINDLEROTATIONTIMESCREENVIEW_HPP
#define SPINDLEROTATIONTIMESCREENVIEW_HPP

#include <gui/spindlerotationtimescreen_screen/SpindleRotationTimeScreenPresenter.hpp>
#include <gui_generated/spindlerotationtimescreen_screen/SpindleRotationTimeScreenViewBase.hpp>

class SpindleRotationTimeScreenView :
    public SpindleRotationTimeScreenViewBase {
public:
    SpindleRotationTimeScreenView();
    virtual ~SpindleRotationTimeScreenView() {}
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

#endif // SPINDLEROTATIONTIMESCREENVIEW_HPP
