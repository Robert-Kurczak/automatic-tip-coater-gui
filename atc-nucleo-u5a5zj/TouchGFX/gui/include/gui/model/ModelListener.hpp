#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include "application/Axes/XAxis/XAxisTestResults.hpp"

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

protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
