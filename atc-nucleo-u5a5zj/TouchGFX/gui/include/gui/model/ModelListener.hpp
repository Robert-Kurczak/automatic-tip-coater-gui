#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include "application/Hardware/Axes/AxisTestResults.hpp"
#include "application/Hardware/Heater/HeaterTestResults.hpp"
#include "application/Rotator/RotatorTestResults.hpp"

#include <gui/model/Model.hpp>

class ModelListener {
public:
    ModelListener() : model(0) {}

    virtual ~ModelListener() {}

    void bind(Model* m) {
        model = m;
    }

    virtual void handleCoatingTaskFinish(bool wasSuccessful) {}
    virtual void handleCalibrationTaskFinish(bool wasSuccessful) {}

    virtual void handleXAxisTestTaskFinish(
        ATC::AxisTestResults results
    ) {}

    virtual void handleYAxisTestTaskFinish(
        ATC::AxisTestResults results
    ) {}

    virtual void handleZAxisTestTaskFinish(
        ATC::AxisTestResults results
    ) {}

    virtual void handleRotatorTestTaskFinish(
        ATC::RotatorTestResults results
    ) {}

    virtual void handleHeaterTestTaskFinish(
        ATC::HeaterTestResults results
    ) {}

protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
