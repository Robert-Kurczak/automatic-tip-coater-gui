#pragma once

#include "application/Axes/XAxis/XAxis.hpp"
#include "application/Axes/YAxis/YAxis.hpp"
#include "application/Axes/ZAxis/ZAxis.hpp"

#include <stdint.h>

namespace ATC {
class Board {
private:
    XAxis& xAxis_;
    YAxis& yAxis_;
    ZAxis& zAxis_;

public:
    Board(XAxis& xAxis, YAxis& yAxis, ZAxis& zAxis);

    void cancelCurrentTask();

    void startCoatingSequence();
    bool isCoatingSequenceFinished();

    void calibrate();
    bool isCalibrationFinished();

    void increaseXAxisStart();
    void decreaseXAxisStart();
    void saveXAxisStart();
    uint32_t getXAxisStart();

    void increaseXAxisEnd();
    void decreaseXAxisEnd();
    void saveXAxisEnd();
    uint32_t getXAxisEnd();

    void increaseXAxisSpeed();
    void decreaseXAxisSpeed();
    void saveXAxisSpeed();
    uint32_t getXAxisSpeed();

    void increaseYAxisStart();
    void decreaseYAxisStart();
    void saveYAxisStart();
    uint32_t getYAxisStart();

    void increaseYAxisEnd();
    void decreaseYAxisEnd();
    void saveYAxisEnd();
    uint32_t getYAxisEnd();

    void increaseYAxisSpeed();
    void decreaseYAxisSpeed();
    void saveYAxisSpeed();
    uint32_t getYAxisSpeed();

    void increaseZAxisStart();
    void decreaseZAxisStart();
    void saveZAxisStart();
    uint32_t getZAxisStart();

    void increaseZAxisEnd();
    void decreaseZAxisEnd();
    void saveZAxisEnd();
    uint32_t getZAxisEnd();

    void increaseZAxisSpeed();
    void decreaseZAxisSpeed();
    void saveZAxisSpeed();
    uint32_t getZAxisSpeed();

    void increaseRotationSpeed();
    void decreaseRotationSpeed();
    void saveRotationSpeed();
    uint32_t getRotationSpeed();

    void setClockwiseRotation();
    void setCounterClockwiseRotation();
    void saveRotationDirection();
    bool isRotationClockwise();

    void testXAxis();
    void testYAxis();
    void testZAxis();
    void testHeater();
};
}