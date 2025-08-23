#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include "application/System/Tasks/SpindleTestTask/SpindleTestResults.hpp"
#include "application/System/Tasks/AxisTestTasks/AxisTestResults.hpp"
#include "application/System/Tasks/HeaterTestTask/HeaterTestResults.hpp"

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

    // TODO only one handler for axes results?
    virtual void handleXAxisTestTaskFinish(ATC::AxisTestResults results) {
    }

    virtual void handleYAxisTestTaskFinish(ATC::AxisTestResults results) {
    }

    virtual void handleZAxisTestTaskFinish(ATC::AxisTestResults results) {
    }

    virtual void handleRotatorTestTaskFinish(
        ATC::SpindleTestResults results
    ) {}

    virtual void handleHeaterTestTaskFinish(
        ATC::HeaterTestResults results
    ) {}

protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
