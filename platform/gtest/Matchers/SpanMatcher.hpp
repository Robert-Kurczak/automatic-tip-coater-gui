#pragma once

#include "gmock/gmock.h"
#include <algorithm>

namespace ATC {
MATCHER_P(SpanRefEq, expected, "") { // NOLINT
    return arg.data() == expected.data() && arg.size() == expected.size();
}

MATCHER_P(SpanValueEq, expected, "") { // NOLINT
    return std::equal(
        arg.begin(), arg.end(), expected.begin(), expected.end()
    );
}
}