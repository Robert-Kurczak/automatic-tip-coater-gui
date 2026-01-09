#pragma once

#include <cstdint>
#include <cstring>
#include <span>

namespace ATC {
template<typename Type>
std::span<const uint8_t> toByteSpan(const Type& data) {
    static_assert(std::is_trivially_copyable_v<Type>);

    return std::span<const uint8_t> {
        // NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast)
        reinterpret_cast<const uint8_t*>(&data),
        sizeof(Type)
        // NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast)
    };
}

template<typename Type>
Type fromByteSpan(const std::span<const uint8_t>& bytes) {
    static_assert(std::is_trivially_copyable_v<Type>);

    Type structure {};
    std::memcpy(&structure, bytes.data(), sizeof(Type)); // NOLINT

    return structure;
}

template<typename Type>
bool areBytesEqual(const Type& left, const Type& right) {
    static_assert(std::is_trivially_copyable_v<Type>);

    return std::memcmp(&left, &right, sizeof(Type)) == 0;
}
}