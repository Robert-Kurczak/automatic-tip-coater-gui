#include "FakeLoggerSink.hpp"

#include <touchgfx/Utils.hpp>

namespace ATC {
ILoggerSink& FakeLoggerSink::operator<<(std::string_view text) {
    touchgfx_printf(text);
    return *this;
}
}