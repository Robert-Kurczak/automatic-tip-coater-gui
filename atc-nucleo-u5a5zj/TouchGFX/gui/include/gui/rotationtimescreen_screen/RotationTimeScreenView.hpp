#ifndef ROTATIONTIMESCREENVIEW_HPP
#define ROTATIONTIMESCREENVIEW_HPP

#include <gui_generated/rotationtimescreen_screen/RotationTimeScreenViewBase.hpp>
#include <gui/rotationtimescreen_screen/RotationTimeScreenPresenter.hpp>

class RotationTimeScreenView : public RotationTimeScreenViewBase
{
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
    static const uint16_t minTimeMs = 0;
    static const uint16_t maxTimeMs = 65000;
    static const uint16_t timeIncrement = 100;

    uint16_t timeMs = 0;
};

#endif // ROTATIONTIMESCREENVIEW_HPP
