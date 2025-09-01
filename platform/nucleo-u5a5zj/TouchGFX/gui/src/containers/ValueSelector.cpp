#include <gui/containers/ValueSelector.hpp>

ValueSelector::ValueSelector() {}

void ValueSelector::initialize() {
    ValueSelectorBase::initialize();
}

void ValueSelector::setDisplayedValue(const uint32_t value) {
    Unicode::snprintf(
        displayedValueBuffer, DISPLAYEDVALUE_SIZE, "%d", value
    );

    displayedValue.invalidate();
}
