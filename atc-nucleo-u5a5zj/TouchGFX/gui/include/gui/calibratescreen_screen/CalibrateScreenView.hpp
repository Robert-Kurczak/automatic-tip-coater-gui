#ifndef CALIBRATESCREENVIEW_HPP
#define CALIBRATESCREENVIEW_HPP

#include <gui_generated/calibratescreen_screen/CalibrateScreenViewBase.hpp>
#include <gui/calibratescreen_screen/CalibrateScreenPresenter.hpp>

class CalibrateScreenView : public CalibrateScreenViewBase
{
public:
    CalibrateScreenView();
    virtual ~CalibrateScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void startCalibration() override;
    virtual void cancelCalibration() override;
protected:
};

#endif // CALIBRATESCREENVIEW_HPP
