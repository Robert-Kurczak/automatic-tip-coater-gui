#ifndef ZAXISSTARTSCREENVIEW_HPP
#define ZAXISSTARTSCREENVIEW_HPP

#include <gui_generated/zaxisstartscreen_screen/ZAxisStartScreenViewBase.hpp>
#include <gui/zaxisstartscreen_screen/ZAxisStartScreenPresenter.hpp>

class ZAxisStartScreenView : public ZAxisStartScreenViewBase
{
public:
    ZAxisStartScreenView();
    virtual ~ZAxisStartScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

protected:
    virtual void increaseButtonPressed() override;
    virtual void decreaseButtonPressed() override;
    virtual void saveButtonPressed() override;

private:
    void updateDisplayedValue();
};

#endif // ZAXISSTARTSCREENVIEW_HPP
