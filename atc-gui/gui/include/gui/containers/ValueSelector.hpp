#ifndef VALUESELECTOR_HPP
#define VALUESELECTOR_HPP

#include <gui_generated/containers/ValueSelectorBase.hpp>

class ValueSelector : public ValueSelectorBase
{
public:
    ValueSelector();
    virtual ~ValueSelector() {}

    virtual void initialize();
    void setDisplayedValue(const uint16_t value);
protected:
};

#endif // VALUESELECTOR_HPP
