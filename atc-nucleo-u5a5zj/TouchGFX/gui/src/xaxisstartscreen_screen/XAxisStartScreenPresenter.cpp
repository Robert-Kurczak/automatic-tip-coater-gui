#include <gui/xaxisstartscreen_screen/XAxisStartScreenPresenter.hpp>
#include <gui/xaxisstartscreen_screen/XAxisStartScreenView.hpp>

XAxisStartScreenPresenter::XAxisStartScreenPresenter(
    XAxisStartScreenView& v
) :
    view(v) {}

void XAxisStartScreenPresenter::activate() {}

void XAxisStartScreenPresenter::deactivate() {}

void XAxisStartScreenPresenter::increaseButtonPressed() {
    model->increaseXAxisStart();
}
