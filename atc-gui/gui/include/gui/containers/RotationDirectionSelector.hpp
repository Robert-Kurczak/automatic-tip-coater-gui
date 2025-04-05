#ifndef ROTATIONDIRECTIONSELECTOR_HPP
#define ROTATIONDIRECTIONSELECTOR_HPP

#include <gui_generated/containers/RotationDirectionSelectorBase.hpp>

class RotationDirectionSelector : public RotationDirectionSelectorBase
{
public:
    RotationDirectionSelector();
    virtual ~RotationDirectionSelector() {}

    virtual void initialize();

    void setClockwiseState(const bool isClockwise);
protected:
};

#endif // ROTATIONDIRECTIONSELECTOR_HPP
