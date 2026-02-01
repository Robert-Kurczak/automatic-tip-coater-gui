#ifndef CALIBRATESCREENVIEW_HPP
#define CALIBRATESCREENVIEW_HPP

#include <gui/calibratescreen_screen/CalibrateScreenPresenter.hpp>
#include <gui_generated/calibratescreen_screen/CalibrateScreenViewBase.hpp>

class CalibrateScreenView : public CalibrateScreenViewBase {
private:
    void displaySettings();

public:
    CalibrateScreenView();
    virtual ~CalibrateScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void startCalibration() override;
    virtual void cancelCalibration() override;

    void resetFooterButtons();
};

#endif // CALIBRATESCREENVIEW_HPP
