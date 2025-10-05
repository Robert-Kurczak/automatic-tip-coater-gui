#pragma once

#include <cstring>
#include <span>
#include <stdint.h>

namespace ATC {
template<typename Type>
std::span<const uint8_t> toByteSpan(const Type& data) {
    static_assert(std::is_trivially_copyable<Type>::value);

    return std::span<const uint8_t> {
        reinterpret_cast<const uint8_t*>(&data), sizeof(data)
    };
}

template<typename Type>
Type fromByteSpan(const std::span<const uint8_t>& bytes) {
    static_assert(std::is_trivially_copyable<Type>::value);

    Type structure {};
    std::memcpy(&structure, bytes.data(), sizeof(Type));

    return structure;
}

template<typename Type>
bool areBytesEqual(const Type& left, const Type& right) {
    static_assert(std::is_trivially_copyable<Type>::value);

    return std::memcmp(&left, &right, sizeof(Type)) == 0;
}
}