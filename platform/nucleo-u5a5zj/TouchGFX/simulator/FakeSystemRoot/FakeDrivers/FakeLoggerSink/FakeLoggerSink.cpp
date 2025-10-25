#include "FakeLoggerSink.hpp"

#include <string>
#include <touchgfx/Utils.hpp>

namespace ATC {
ILoggerSink& FakeLoggerSink::operator<<(std::string_view text) {
    touchgfx_printf(std::string(text).c_str());

    return *this;
}
}