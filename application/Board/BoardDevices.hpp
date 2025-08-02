#pragma once

#include "application/Hardware/Axes/XAxis/IXAxis.hpp"
#include "application/Hardware/Axes/YAxis/IYAxis.hpp"
#include "application/Hardware/Axes/ZAxis/IZAxis.hpp"
#include "application/Hardware/FramebufferDisplay/IFramebufferDisplay.hpp"
#include "application/Hardware/Heater/IHeater.hpp"
#include "application/Hardware/Rotator/IRotator.hpp"
#include "application/TouchControllerXpt2046/TouchControllerXpt2046.hpp"

// TODO relay on interfaces
namespace ATC {
struct BoardDevices {
    IXAxis& xAxis;
    IYAxis& yAxis;
    IZAxis& zAxis;
    IRotator& rotator;
    IHeater& heater;
    IFramebufferDisplay& display;
    TouchControllerXpt2046& touchController;
};
}