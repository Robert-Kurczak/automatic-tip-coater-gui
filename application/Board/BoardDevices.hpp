#pragma once

#include "application/Axes/XAxis/XAxis.hpp"
#include "application/Axes/YAxis/YAxis.hpp"
#include "application/Axes/ZAxis/ZAxis.hpp"
#include "application/DisplayWs17143/DisplayWs17143.hpp"
#include "application/TouchControllerXpt2046/TouchControllerXpt2046.hpp"

// TODO relay on interfaces
namespace ATC {
struct BoardDevices {
    XAxis& xAxis;
    YAxis& yAxis;
    ZAxis& zAxis;
    DisplayWs17143& display;
    TouchControllerXpt2046& touchController;
};
}