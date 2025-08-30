#ifndef SPINDLEROTATIONTIMESCREENVIEW_HPP
#define SPINDLEROTATIONTIMESCREENVIEW_HPP

#include <gui_generated/spindlerotationtimescreen_screen/SpindleRotationTimeScreenViewBase.hpp>
#include <gui/spindlerotationtimescreen_screen/SpindleRotationTimeScreenPresenter.hpp>

class SpindleRotationTimeScreenView : public SpindleRotationTimeScreenViewBase
{
public:
    SpindleRotationTimeScreenView();
    virtual ~SpindleRotationTimeScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SPINDLEROTATIONTIMESCREENVIEW_HPP
