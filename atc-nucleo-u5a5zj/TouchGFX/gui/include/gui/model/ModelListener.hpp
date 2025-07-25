#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include "application/Axes/XAxis/XAxisTestResults.hpp"
#include "application/Axes/YAxis/YAxisTestResults.hpp"
#include "application/Axes/ZAxis/ZAxisTestResults.hpp"
#include "application/Heater/HeaterTestResults.hpp"
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
        ATC::XAxisTestResults results
    ) {}

    virtual void handleYAxisTestTaskFinish(
        ATC::YAxisTestResults results
    ) {}

    virtual void handleZAxisTestTaskFinish(
        ATC::ZAxisTestResults results
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
