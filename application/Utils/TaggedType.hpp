#pragma once

namespace ATC {
template<typename TagType, typename ValueType>
struct TaggedType {
    ValueType value;

    constexpr explicit TaggedType(const ValueType& value) :
        value(value) {}
};
}